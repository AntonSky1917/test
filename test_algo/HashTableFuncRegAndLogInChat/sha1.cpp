#include "sha1.h"
#include <cstring> // Для использования функций strcpy, strcmp, strlen
#include <cstdint> // Для использования типа uint32_t

uint32_t cycle_shift_left(uint32_t val, int bit_count) {
    return (val << bit_count | val >> (32-bit_count));
}

uint32_t bring_to_human_view(uint32_t val) {
    return  ((val & 0x000000FF) << 24) | 
            ((val & 0x0000FF00) << 8) | 
            ((val & 0x00FF0000) >> 8) | 
            ((val & 0xFF000000) >> 24);
}

uint32_t* sha1(char* message, uint32_t msize_bytes) {
    //инициализация
    uint32_t A = H[0];
    uint32_t B = H[1];
    uint32_t C = H[2];
    uint32_t D = H[3];
    uint32_t E = H[4];
    
    // подсчет целого числа блоков
    uint32_t totalBlockCount = msize_bytes  / one_block_size_bytes;
    
    // подсчет, сколько байт нужно, чтобы дополнить последний блок
    uint32_t needAdditionalBytes = 
        one_block_size_bytes - (msize_bytes - totalBlockCount * one_block_size_bytes);
        
    if(needAdditionalBytes < 8) {
        totalBlockCount += 2;
        needAdditionalBytes += one_block_size_bytes;
    } else {
        totalBlockCount += 1;
    }
    
    // размер дополненного по всем правилам сообщения
    uint32_t extendedMessageSize = msize_bytes + needAdditionalBytes;
    
    // выделяем новый буфер и копируем в него исходный
    unsigned char* newMessage = new unsigned char[extendedMessageSize];
    memcpy(newMessage, message, msize_bytes);
    
    // первый бит ставим '1', остальные обнуляем
    newMessage[msize_bytes] = 0x80;    
    memset(newMessage + msize_bytes + 1, 0, needAdditionalBytes - 1);
    
    // задаем длину исходного сообщения в битах
    uint32_t* ptr_to_size = (uint32_t*) (newMessage + extendedMessageSize - 4); 
    *ptr_to_size =  bring_to_human_view(msize_bytes * 8);
    
    ExpendBlock exp_block;
    //раунды поехали
    for(int i=0; i<totalBlockCount; i++) {
        
        // берем текущий блок и дополняем его
        unsigned char* cur_p = newMessage + one_block_size_bytes * i;
        Block block = (Block) cur_p;
        
        // первые 16 4байтовых чисел
        for (int j=0; j<one_block_size_uints; j++) {
            exp_block[j] = bring_to_human_view(block[j]);
        }
        // следующие 64...
        for (int j=one_block_size_uints; j < block_expend_size_uints; j++) {
            exp_block[j] = 
                exp_block[j-3] ^ 
                    exp_block[j-8] ^ 
                      exp_block[j-14] ^ 
                        exp_block[j-16];
            exp_block[j] = cycle_shift_left(exp_block[j], 1);
        }
            
        // инициализация 
        uint32_t a = H[0];
        uint32_t b = H[1];
        uint32_t c = H[2];
        uint32_t d = H[3];
        uint32_t e = H[4];

        // пересчитываем
        for(int j=0;j < block_expend_size_uints; j++) {
            uint32_t f;
            uint32_t k;
            // в зависимости от раунда считаем по-разному
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
        
            // перемешивание
            uint32_t temp = cycle_shift_left(a,5) + f + e + k + exp_block[j];
            e = d;
            d = c;
            c = cycle_shift_left(b,30);
            b = a;
            a = temp;   
        }
        // пересчитываем
        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
    }
    
    // A,B,C,D,E являются выходными 32б составляющими посчитанного хэша
    uint32_t* digest = new uint32_t[5];
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    
    // чистим за собой
    delete[] newMessage;
    return digest;
}