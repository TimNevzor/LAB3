#include "modAlphaCipher.cpp"
#include "modAlphaCipher.h"
using namespace std;
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK(L"ЬЪМШДРЛАП" == modAlphaCipher(L"КЛЮЧ").encrypt(L"СООБЩЕНИЕ"));
    }
    TEST(LongKey) {
        CHECK(L"ЧП" == modAlphaCipher(L"СИНХРОФАЗАТРОН").encrypt(L"ЁЖ"));
    }
    TEST(LowCaseKey) {
        CHECK(L"ЬЪМШДРЛАП" == modAlphaCipher(L"ключ").encrypt(L"СООБЩЕНИЕ"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp(L"ключ123"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp(L"ключ,"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L"К л ю ч"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""), cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp(L"ААА"), cipher_error);
    }
}
struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"ТЫЁЩЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ" == p->encrypt(L"СЪЕШЬЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЖЕЧАЮ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(L"ТЫЁЩЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ" == p->encrypt(L"съешьещёэтихмягкихфранцузскихбулокдавыпейжечаю"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK(L"ТЫЁЩЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ" == p->encrypt(L"СЪЕШЬ, ЕЩЁ, ЭТИХ, МЯГКИХ, ФРАНЦУЗСКИХ, БУЛОК, ДА, ВЫПЕЙ, ЖЕ, ЧАЮ!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK(L"ЛСЙРЁС" == p->encrypt(L"крипер2004"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt(L"2+2=4"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(L"РЩДЧЫДШЕЬСЗФЛЮВЙЗФУПЯМХТЖРЙЗФАТКНЙГЯБЪОДИЁДЦЯЭ" == modAlphaCipher(L"Я").encrypt(L"СЪЕШЬЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЖЕЧАЮ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"СЪЕШЬЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЖЕЧАЮ" == p->decrypt(L"ТЫЁЩЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"тыёщЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt(L"СЪЕШЬ ЕЩЁ ЭТИХ МЯГКИХ ФРАНЦУЗСКИХ БУЛОК ДА ВЫПЕЙ ЖЕ ЧАЮ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt(L"крипер2004"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(L"ТЫЁЩЭЁЪЖЮУЙЦНАДЛЙЦХСБОЧФИТЛЙЦВФМПЛЕБГЬРЁКЗЁШБЯ!!!!!!!"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK(L"СЪЕШЬЕЩЁЭТИХМЯГКИХФРАНЦУЗСКИХБУЛОКДАВЫПЕЙЖЕЧАЮ" == modAlphaCipher(L"Я").decrypt(L"РЩДЧЫДШЕЬСЗФЛЮВЙЗФУПЯМХТЖРЙЗФАТКНЙГЯБЪОДИЁДЦЯЭ"));
    }
}

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    return UnitTest::RunAllTests();
}
