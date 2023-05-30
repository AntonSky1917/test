#include "hash_table.h"
#include <cstring> // Для использования функций strcpy, strcmp, strlen
#include <cstdint> // Для использования типа uint32_t

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    for (int i = 0; i < mem_size; i++) {
        delete[] array[i].pass_sha1_hash;
    }
    delete[] array;
}

void HashTable::resize() {
    int new_mem_size = mem_size * 2;
    Pair* new_array = new Pair[new_mem_size];
    for (int i = 0; i < mem_size; i++) {
        if (array[i].pass_sha1_hash != nullptr) {
            int index = hash_func(array[i].login);
            int attempt = 0;
            while (new_array[index].pass_sha1_hash != nullptr) {
                attempt++;
                index = probe_func(index, attempt);
            }
            new_array[index] = array[i];
        }
    }
    delete[] array;
    array = new_array;
    mem_size = new_mem_size;
}

void HashTable::add(char _login[LOGINLENGTH], uint32_t* sh1) {
    int index = hash_func(_login);
    int attempt = 0;
    while (array[index].pass_sha1_hash != nullptr) {
        attempt++;
        index = probe_func(index, attempt);
    }
    
    if (count >= mem_size / 2) {
        resize();
        add(_login, sh1);
    } else {
        array[index] = Pair(_login, sh1);
        count++;
    }
}

uint32_t* HashTable::get(char _login[LOGINLENGTH]) {
    int index = hash_func(_login);
    int attempt = 0;
    while (array[index].pass_sha1_hash != nullptr) {
        if (strcmp(array[index].login, _login) == 0) {
            return array[index].pass_sha1_hash;
        }
        attempt++;
        index = probe_func(index, attempt);
    }
    return nullptr;
}

int HashTable::hash_func(char _login[LOGINLENGTH]) {
    int sum = 0;
    int i = 0;
    for (; i < strlen(_login); i++) {
        sum += _login[i];
    }
    return (sum * 2654435761 % mem_size);
}

int HashTable::probe_func(int index, int attempt) {
    return (index + attempt * attempt) % mem_size;
}