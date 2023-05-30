#pragma once

#include "sha1.h"
#include "hash_table.h"

class Chat {
public:
    Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
    
private:
    HashTable hash_table;
};