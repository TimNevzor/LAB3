//main.cpp
#include "cipher.h"
SUITE(KeyTest)
{
    TEST(ValidKey) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("eywtqr", encryptor.encrypt("qwerty"));
    }
    TEST(NegativeKey) {
        string key = "-3";
        CHECK_THROW(cipher encryptor(key), cipher_error);
    }
    TEST(FloatKey) {
        string key = "3.14";
        cipher encryptor(key);
        CHECK_EQUAL("eywtqr", encryptor.encrypt("qwerty"));
    }
    TEST(EmptyKey) {
        string key = "";
        CHECK_THROW(cipher encryptor(key), cipher_error);
    }
    TEST(CharKey) {
        string key = "3yeah";
        cipher encryptor(key);
        CHECK_EQUAL("eywtqr", encryptor.encrypt("qwerty"));
    }
    TEST(TooBigKey) {
        string key = "10000";
        cipher encryptor(key);
        CHECK_EQUAL("eywtqr", encryptor.encrypt("qwerty"));
    }
}

SUITE(EncryptTest)
{
    TEST(UpString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("EYWTQR", encryptor.encrypt("QWERTY"));
    }
    TEST(LowString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("eywtqr", encryptor.encrypt("qwerty"));
    }
    TEST(PunctuationText) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("etwrq!y", encryptor.encrypt("qwe!rty"));
    }
    TEST(DigestText) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("etwrq3y", encryptor.encrypt("qwe3rty"));
    }
    TEST(EmptyString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("", encryptor.encrypt(""));
    }
}
SUITE(DecryptTest)
{
    TEST(UpString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("QWERTY", encryptor.decrypt("EYWTQR"));
    }
    TEST(LowString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("qwerty", encryptor.decrypt("eywtqr"));
    }
    TEST(PunctuationText) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("qwe!rty", encryptor.decrypt("etwrq!y"));
    }
    TEST(DigestText) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("qwe3rty", encryptor.decrypt("etwrq3y"));
    }
    TEST(EmptyString) {
        string key = "3";
        cipher encryptor(key);
        CHECK_EQUAL("", encryptor.decrypt(""));
    }
}
int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}
