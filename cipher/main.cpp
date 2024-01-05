#include <iostream>
#include <fstream>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/hex.h>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"

using namespace std;
using namespace CryptoPP;

void encrypt() {
    ifstream fs;
    ofstream fs2;
    ifstream fs3;
    string str;
    string strs = "";
    string file;
    cout << "Введите имя файла, откуда считать:";
    cin >> file;
    fs.open(file); 
    char ch;
    while (fs.get(ch)) {
        strs.push_back(ch); 
    }
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE]; 
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH); 
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string plaintext = strs;
    string ciphertext;
    cout << plaintext;
    cout << endl;
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext)); 
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()); 
    stfEncryptor.MessageEnd(); 
    for (int i = 0; i < ciphertext.size(); i++) {
        cout << hex << (0xFF & static_cast<byte>(ciphertext[i]));
    }
    cout << "\nВведите имя файла, в который записать: ";
    string imp, file2;
    cin >> file2;
    fs2.open(file2);
    for (int i = 0; i < ciphertext.size(); i++) {
        fs2 << ciphertext[i];
    }
}
void decrypt() {
    ifstream fs;
    ofstream fs2;
    ifstream fs3;
    string str;
    string strs = "";
    string file;
    cout << "Введите имя файла, откуда считать:";
    cin >> file;
    fs.open(file);
    char ch;
    while (fs.get(ch)) {
        strs.push_back(ch);
    }
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string plaintext = strs;
    string decryptedtext;
    cout << "Plain Text (" << plaintext.size() << " bytes)" << endl;
    cout << plaintext;
    cout << endl;
    string imp, file2;
    cout << "Введите имя файла, в который записать: ";
    cin >> file2;
    fs2.open(file2);
    fs3.open(file2);
    cout << endl;
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH); //создаем объект класса для дешифрования с использованием ключа
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv); //создаем объект класса для блочного дешифрования
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext)); //инициализируем объект класса для симметричного дешифрования
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
    stfDecryptor.MessageEnd();
    cout << decryptedtext << endl;
    fs2 << decryptedtext;
}

int main()
{
    ifstream fs;
    ofstream fs2;
    ifstream fs3;
    string str;
    string strs = "";
    string file, str9;
    string t;
    int k, key;
    cout << "Ведите ключ: ";
    cin >> key;
            do {
                cout << "0 - выйти, 1 - зашифровать, 2 - расшифровать:";
                cin >> k;
                if (k == 1) {
                    encrypt();
                }
                else  if (k == 2) {
                    decrypt();
                }
            } while (k != 0);
    return 0;
}
