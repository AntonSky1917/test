#include "iostream"
#include "chat.h"
#include <cstring> // Для использования функций strcpy, strcmp, strlen
#include <cstdint> // Для использования типа uint32_t

Chat::Chat() {}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    hash_table.add(_login, sha1(_pass, pass_length));
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint32_t* digest = sha1(_pass, pass_length);
    uint32_t* stored_hash = hash_table.get(_login);
    
    bool cmpHashes = (stored_hash != nullptr) && (!memcmp(stored_hash, digest, SHA1HASHLENGTHBYTES));
    
    delete[] digest;
    
    return cmpHashes;
}

int main() {
    Chat chat;

    // Регистрация пользователей
    chat.reg("user1", "password1", strlen("password1"));
    chat.reg("user2", "password2", strlen("password2"));
    chat.reg("user3", "password3", strlen("password3"));

    // Попытка входа пользователей
    std::cout << "User 1 login: " << (chat.login("user1", "password1", strlen("password1")) ? "Success" : "Failed") << std::endl;
    std::cout << "User 2 login: " << (chat.login("user2", "wrong_password", strlen("wrong_password")) ? "Success" : "Failed") << std::endl;
    std::cout << "User 3 login: " << (chat.login("user3", "password3", strlen("password3")) ? "Success" : "Failed") << std::endl;

    return 0;
}