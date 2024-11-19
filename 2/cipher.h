//cipher.h
#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <UnitTest++/UnitTest++.h>
using namespace std;

class cipher
{
private:
    int columns;
    string valmes;
    int getValidKey(string& key);
    string getValidText(string& message);
public:
    cipher(string key);
    cipher() = delete;
    string encrypt(string message);
    string decrypt(string message);
};

class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg): std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg): std::invalid_argument(what_arg) {}

};
