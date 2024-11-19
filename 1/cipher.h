#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <stdexcept>
#include <codecvt>
#include <UnitTest++/UnitTest++.h>
using namespace std;
class modAlphaCipher
{
private:
    wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    map<wchar_t, int> alphaNum;                     //ассоциативный массив "номер по символу"
    vector<int> key;                                //ключ
    vector<int> convert(const wstring& s);          //преобразование вектор-строка
    wstring convert(const vector<int>& v);          //преобразование строка-вектор
    wstring getValidKey(const wstring & s);
    wstring getValidOpenText(const wstring& s);
    wstring getValidCipherText(const wstring& s);

public:
    modAlphaCipher() = delete;                      //запертим конструктор без параметров
    modAlphaCipher(const wstring& skey);            //конструктор для установки ключа
    wstring encrypt(const wstring& open_text);      //зашифрование
    wstring decrypt(const wstring& cipher_text);    //расшифрование
};
class cipher_error : public invalid_argument
{
public: //подключает invalid_argument для обработки некорректных данных
    explicit cipher_error(const string& what_arg): invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg): invalid_argument(what_arg) {}
};
