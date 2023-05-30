#pragma once

#include <cstring> // Для использования функций strcpy, strcmp, strlen
#include <cstdint> // Для использования типа uint32_t

typedef unsigned int uint32_t;

#define one_block_size_bytes 64 // количество байб в блоке
#define one_block_size_uints 16 // количество 4байтовых  в блоке
#define block_expend_size_uints 80 // количество 4байтовых в дополненном блоке

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef uint32_t* Block;
typedef uint32_t ExpendBlock[block_expend_size_uints];

const uint32_t H[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
}; // константы, согласно стандарту

uint32_t cycle_shift_left(uint32_t val, int bit_count);
uint32_t bring_to_human_view(uint32_t val);

uint32_t* sha1(char* message, uint32_t msize_bytes); // отданный массив нужно удалить вручную