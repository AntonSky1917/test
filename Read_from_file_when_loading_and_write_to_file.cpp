#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

class User {
    string _name;
    string _login;
    string _pass;

public:
    string getName() const { return _name; }
    string getLogin() const { return _login; }
    string getPass() const { return _pass; }

    void setName(const string& name) { _name = name; }
    void setLogin(const string& login) { _login = login; }
    void setPass(const string& pass) { _pass = pass; }

    void printInfo(ofstream& file) {
        file << "Name: " << _name << endl;
        file << "Login: " << _login << endl;
        file << "Password: " << _pass << endl;
    }

    void readInfo(ifstream& file) {
        string line;
        while (getline(file, line)) {
            if (line.find("Name: ") == 0) {
                _name = line.substr(6);
            } else if (line.find("Login: ") == 0) {
                _login = line.substr(7);
            } else if (line.find("Password: ") == 0) {
                _pass = line.substr(10);
            }
        }
    }
};

class Message {
    string _text;
    string _sender;
    string _receiver;

public:
    string getText() const { return _text; }
    string getSender() const { return _sender; }
    string getReceiver() const { return _receiver; }

    void setText(const string& text) { _text = text; }
    void setSender(const string& sender) { _sender = sender; }
    void setReceiver(const string& receiver) { _receiver = receiver; }

    void printInfo(ofstream& file) {
        file << "Text: " << _text << endl;
        file << "Sender: " << _sender << endl;
        file << "Receiver: " << _receiver << endl;
    }

    void readInfo(ifstream& file) {
        string line;
        while (getline(file, line)) {
            if (line.find("Text: ") == 0) {
                _text = line.substr(6);
            } else if (line.find("Sender: ") == 0) {
                _sender = line.substr(8);
            } else if (line.find("Receiver: ") == 0) {
                _receiver = line.substr(10);
            }
        }
    }
};

int main() {
    // Создание объектов User и Message
    User user;
    user.setName("123");
    user.setLogin("gogo");
    user.setPass("password");

    Message message;
    message.setText("WAAAAAAATSAAAAAAAAPPPP");
    message.setSender("gogo");
    message.setReceiver("mimimi");

    // Установка маски прав доступа
    umask(S_IRWXG | S_IRWXO); // Устанавливаем права доступа только для владельца

    // Запись состояния объектов в файлы
    ofstream userFile("user.txt");
    if (userFile.is_open()) {
        user.printInfo(userFile);
        userFile.close();

        // Установка прав доступа к файлу только для владельца
        chmod("user.txt", S_IRUSR | S_IWUSR);
    } else {
        cerr << "Не удалось открыть user.txt" << endl;
        return 1;
    }

    ofstream messageFile("message.txt");
    if (messageFile.is_open()) {
        message.printInfo(messageFile);
        messageFile.close();

        // Установка прав доступа к файлу только для владельца
        chmod("message.txt", S_IRUSR | S_IWUSR);
    } else {
        cerr << "Не удалось открыть message.txt" << endl;
        return 1;
    }

    // Чтение состояния объектов из файлов
    ifstream userFileRead("user.txt");
    if (userFileRead.is_open()) {
        User userRead;
        userRead.readInfo(userFileRead);

        // Вывод считанной информации
        cout << "User Info:" << endl;
        cout << "Name: " << userRead.getName() << endl;
        cout << "Login: " << userRead.getLogin() << endl;
        cout << "Password: " << userRead.getPass() << endl;

        cout << endl;

        userFileRead.close();
    } else {
        cerr << "Не удалось открыть user.txt" << endl;
        return 1;
    }

    ifstream messageFileRead("message.txt");
    if (messageFileRead.is_open()) {
        Message messageRead;
        messageRead.readInfo(messageFileRead);

        cout << "Message Info:" << endl;
        cout << "Text: " << messageRead.getText() << endl;
        cout << "Sender: " << messageRead.getSender() << endl;
        cout << "Receiver: " << messageRead.getReceiver() << endl;

        messageFileRead.close();
    } else {
        cerr << "Не удалось открыть message.txt" << endl;
        return 1;
    }

    const char* fileName = "user.txt";
    const char* messageFileName = "message.txt";

    struct stat fileStat;
    if (stat(fileName, &fileStat) == 0) {
        // Получение прав доступа файла
        mode_t filePermissions = fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

        // Проверка, что права доступа только для владельца
        if ((filePermissions & (S_IRWXG | S_IRWXO)) == 0) {
            std::cout << "Права доступа к файлу " << fileName << " только для владельца" << std::endl;
        } else {
            std::cout << "Права доступа к файлу " << fileName << " не установлены только для владельца" << std::endl;
        }
    } else {
        std::cerr << "Ошибка при получении информации о файле " << fileName << std::endl;
        return 1;
    }

    // Проверка прав доступа для message.txt
    struct stat messageFileStat;
    if (stat(messageFileName, &messageFileStat) == 0) {
        // Получение прав доступа файла
        mode_t messageFilePermissions = messageFileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

        // Проверка, что права доступа только для владельца
        if ((messageFilePermissions & (S_IRWXG | S_IRWXO)) == 0) {
            std::cout << "Права доступа к файлу " << messageFileName << " только для владельца" << std::endl;
        } else {
            std::cout << "Права доступа к файлу " << messageFileName << " не установлены только для владельца" << std::endl;
        }
    } else {
        std::cerr << "Ошибка при получении информации о файле " << messageFileName << std::endl;
        return 1;
    }

    return 0;
}
