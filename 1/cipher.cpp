#include "modAlphaCipher.h"
using namespace std;
modAlphaCipher::modAlphaCipher(const wstring& skey)
{
    for(unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
    int n = 0;
    for (auto e : key) {
        if (e == 0) {
            n++;
        }
    }
    if (2 * n > static_cast<int>(key.size())) {
        throw cipher_error("WeakKey");
    }
}
wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for(auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for(auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
wstring modAlphaCipher::getValidKey(const wstring& s)
{
    if(s.empty())
        throw cipher_error("Empty key");
    wstring tmp(s);
    for(auto& c : tmp) {
        if(!iswalpha(c))
            throw cipher_error(string("Invalid key"));
        if(iswlower(c))
            c = towupper(c);
    }
    return tmp;
}
inline wstring modAlphaCipher::getValidOpenText(const wstring& s)
{
    wstring tmp;
    for(auto c : s) {
        if(iswalpha(c)) {
            if(iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if(tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}
inline wstring modAlphaCipher::getValidCipherText(const wstring& s)
{
    if(s.empty())
        throw cipher_error("Empty cipher text");
    for(auto c : s) {
        if(!iswupper(c))
            throw cipher_error(string("Invalid cipher text"));
    }
    return s;
}
