#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <thread>
#include <shared_mutex>

void userReg(std::string& curName, std::string& curPassWord);   // ������� ��� ����� ������ ������������ ��� ����������� ��� �����

class PersMessage                                      // ����� ��������� �������������
{
    std::string persName;
    std::string persDirWord;
    std::string textInfo;
public:
    PersMessage();
    std::string getCharValue(int fieldNumber) const;   // �������-������ ��� ������ ����� ������ ���� stringt
    void setValue(int numValue, std::string value);    // ������� ������ ��� ������������� ����� ���� string
    void initPersMessage(std::string persName);
};

class Chat
{
    std::map <std::string, std::string> persArray;      // ������ � ������� �������������
    std::vector<PersMessage> messArray;                      // ������ � �����������
public:
    void entrChat(bool& persPresence, std::string& curName, std::string& curPassWord);     // ����� � ���
    void regChat(bool& nameInChatAlready, bool& persPresence, std::string& curName, std::string& curPassWord);    // ������������������ � ����
    bool ifEmpty();                               // ���� � ������� ���� ���������
    void showMess(std::string curName);           // �������� ���������
    void delMess();                               // ������� ���������
    std::string sendMess(std::string curName);    // ��������� ���������
};

class Logger
{
    std::fstream fileStream; // ���� ������ fstream
    //std::shared_mutex shared_mutex;
public:
    Logger();  // ����������� ������������ ������
    ~Logger(); // ���������� ������������ ������
    void writeToFile(std::shared_mutex& shrMx, std::string message); // to write into the file
    void readFromFile(std::shared_mutex& shrMx); // to read a string from the file
};

void logToFile(std::shared_mutex& shrMx, std::string mess);     // ������� ����������� ��������� � ������� ��������������� ������

void logFromFile(std::shared_mutex& shrMx);                     // ������� ������ ��������� � ������� ��������������� ������               

// ���. ������������� 27.11.2024