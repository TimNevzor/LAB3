//cipher.cpp
#include "cipher.h"
cipher::cipher(string key)
{
    columns = getValidKey(key); //получение кол-ва столбцов
}
bool allowedsymbolsfunc(char sym) //ф-ция принимает символ из введенной пользователем строки
{
    //строка допустимых символов
    string allowedsymbolslist = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&()_+-=[]{}";
    for (char i : allowedsymbolslist) {
        if(sym == i) { //если символ принадлежит к допустимым, то возвращается true
            return true;
        }
    }
    return false;
}
string cipher::getValidText(string& message) //ф-ция формирования допустимой строки
{
    string validMessage;
    for (char c : message) {
        if (allowedsymbolsfunc(c)) {
            validMessage += c;
        }
    }
    return validMessage;
}

int cipher::getValidKey(string& key) // проверка на допустимость ключа
{
    if (key.empty()) {
        throw cipher_error("Key must not be empty");// проверяем, что строка не пустая
    }
    int nkey = stoi(key);
    if (nkey <= 0) { // проверяем, что ключ неотрицательный
        throw cipher_error("Key must be a non-negative integer");
    }
    return nkey;
}

string cipher::encrypt(string oldmessage)       //ф-ция зашифрования
{
    string stroka = getValidText(oldmessage);   //получение допустимой строки
    string endmessage;
    int meslen = stroka.length();               //получение длины строки
    if (meslen <= columns) {
        columns = meslen / 2;
    }
    int lines = ceil(double(meslen) / columns); //число строк
    char tab[lines][columns] = {'*'};           //таблица, заполненная символом-заполнителем "*"
    int counter = 0;
    for (int i = 0; i < lines; ++i) {           //формирование таблицы
        for (int j = 0; j < columns; ++j) {
            if (counter < meslen) {
                tab[i][j] = stroka[counter++];
            }
        }
    }
    for (int i = columns - 1; i >= 0; --i) {    //формирование зашифрованной строки
        for (int j = 0; j < lines; ++j) {
            endmessage += tab[j][i];
        }
    }
    string meswithoutsym = "";                  //очистка вывода от символа-заполнителя "*"
    for(char i : endmessage) {
        if(i != '*') {
            meswithoutsym += i;
        }
    }
    string finalmessage;                        //очистка вывода от мусорных символов
    for (char c : meswithoutsym) {
        if (oldmessage.find(c) != string::npos) {
            finalmessage += c;
        }
    }
    return finalmessage;
}
string cipher::decrypt(string oldmessage)       //ф-ция расшифрования
{
    string stroka = getValidText(oldmessage);   //получение допустимой строки
    int meslen = stroka.length();               //получение длины строки
    if (meslen == 0) {                          //если строка пустая, то вернется пустое сообщение
        return "";
    }
    int n = meslen;
    string endmessage;
    int lines = ceil(double(meslen) / columns); //число строк
    char tab[lines][columns];                   //таблица
    int strwithfillsym = lines - 1;             //строка с заполняющими символами
    int c1 = 0;
    int c2 = 0;
    while (n % columns != 0)
        n++;
    //формирование таблицы
    for (int j = columns - 1; j >= 0; --j) {
        if (c1 < n - meslen) {
            tab[strwithfillsym][j] = '*';
            c1++;
        } else {
            break;
        }
    }
    for (int j = columns - 1; j >= 0; --j) {
        for (int i = 0; i < lines; ++i) {
            if (c2 < meslen && tab[i][j] != '*') {
                tab[i][j] = stroka[c2++];
            }
        }
    }
    for (int i = 0; i < lines; ++i) {   //формирование зашифрованной строки
        for (int j = 0; j < columns; ++j) {
            endmessage += tab[i][j];
        }
    }
    string meswithoutsym = "";  //очистка вывода от символа-заполнителя "*"
    for(char i : endmessage) {
        if(i != '*') {
            meswithoutsym += i;
        }
    }
    string finalmessage;  //очистка вывода от мусорных символов
    for (char c : meswithoutsym) {
        if (oldmessage.find(c) != string::npos) {
            finalmessage += c;
        }
    }
    return finalmessage;
}
