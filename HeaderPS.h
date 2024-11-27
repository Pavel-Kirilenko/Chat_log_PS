#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <shared_mutex>

void userReg(std::string& curName, std::string& curPassWord);   // функция для ввода данных пользователя при регистрации или входе

class PersMessage                                      // класс сообщений пользователей
{
    std::string persName;
    std::string persDirWord;
    std::string textInfo;
public:
    PersMessage();
    std::string getCharValue(int fieldNumber) const;   // функция-геттер для вывода полей класса типа stringt
    void setValue(int numValue, std::string value);    // функция сеттер для инициализации полей типа string
    void initPersMessage(std::string persName);
};

class Chat
{
    std::map <std::string, std::string> persArray;      // массив с данными пользователей
    std::vector<PersMessage> messArray;                      // массив с сообщениями
public:
    void entrChat(bool& persPresence, std::string& curName, std::string& curPassWord);     // войти в чат
    void regChat(bool& nameInChatAlready, bool& persPresence, std::string& curName, std::string& curPassWord);    // зарегистрироваться в чате
    bool ifEmpty();                               // если в массиве есть сообщения
    void showMess(std::string curName);           // показать сообщения
    void delMess();                               // удалить сообщение
    std::string sendMess(std::string curName);    // отправить сообщение
};

class Logger
{
    std::fstream fileStream; // поле метода fstream
    //std::shared_mutex shared_mutex;
public:
    Logger();  // конструктор логгирующего класса
    ~Logger(); // деструктор логгирующего класса
    void writeToFile(std::shared_mutex& shrMx, std::string message); // to write into the file
    void readFromFile(std::shared_mutex& shrMx); // to read a string from the file
};

void logToFile(std::shared_mutex& shrMx, std::string mess);     // функция логирования сообщений с помощью дополнительного потока

void logFromFile(std::shared_mutex& shrMx);                     // функция чтения сообщений с помощью дополнительного потока               

// пос. Магистральный 27.11.2024