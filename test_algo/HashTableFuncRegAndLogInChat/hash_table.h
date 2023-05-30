#pragma once
#include <cstring> // Для использования функций strcpy, strcmp, strlen
#include <cstdint> // Для использования типа uint32_t

#define SIZE 10
#define LOGINLENGTH 10

class HashTable {
public:
    HashTable();
    ~HashTable();
    void add(char _login[LOGINLENGTH], uint32_t* sh1);
    uint32_t* get(char _login[LOGINLENGTH]);
    
private:
    struct Pair { // пара ключ-значение
        Pair():
            login(""),
            pass_sha1_hash(nullptr)
        {}
        
        Pair(char _login[LOGINLENGTH], uint32_t* sh1):
            pass_sha1_hash(sh1)
        {
            strcpy(login, _login);
        }
        
        char login[LOGINLENGTH];
        uint32_t* pass_sha1_hash;
    };
    
    void resize();
    int hash_func(char _login[LOGINLENGTH]);
    int probe_func(int index, int attempt);
    
    Pair* array;
    int mem_size;
    int count;
};