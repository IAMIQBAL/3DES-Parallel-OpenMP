#include <iostream>
#include "P3DES.h"

using namespace std;
#define LOG(X) cout << X << endl;
#define LOGN(X) cout << X;

int main(){

    LOG("1: 3DES Serial");
    LOG("2: 3DES Parallel");
    LOG("3: 3DES Sbox Parallel");
    LOG("4: 3DES Nested Parallelism");

    LOGN("Mode: ");
    int mode = 0;
    cin >> mode;

    LOGN("Show Decrypted Output: ");
    int op = 0;
    cin >> op;

    LOGN("Threads: ");
    int threads = 0;
    cin >> threads;

    LOGN("File path: ");
    string fName = "";
    cin >> fName;

    string k1 = Key1;
    string k2 = Key2;
    string k3 = Key3;

    vector<string> text = readFile(fName);
    int size = text.size();
    string* data = new string[size];
    for (int i = 0; i < size; i++){
        data[i] = text[i];
    }

    if (mode == 1){

        LOG("File Read Complete...");
        S3DES *d3 = new S3DES(k1, k2, k3, size);
        string *enc = new string[size];

        LOG("Encrypting... " << endl);
        enc = d3->pEncrypt(data);
        writeFileStr("enc.txt", enc, size);

        LOG("Decrypting... ");
        S3DES *d3_2 = new S3DES(k1, k2, k3, size);
        string *plain = new string[size];
        plain = d3_2->pDecrypt(enc);

        string result = "";
        for (int i = 0; i < size; i++){
            result += plain[i];
        }
        if (op == 1){
            LOG(result);
        }
    } else if (mode == 2){

        LOG("File Read Complete...");
        P3DES *d3 = new P3DES(k1, k2, k3, threads, size, 0);
        string *enc = new string[size];

        LOG("Encrypting...");
        enc = d3->pEncrypt(data);
        writeFileStr("enc.txt", enc, size);

        LOG("Decrypting...");
        P3DES *d3_2 = new P3DES(k1, k2, k3, threads, size, 0);
        string *plain = new string[size];
        plain = d3_2->pDecrypt(enc);

        string result = "";
        for (int i = 0; i < size; i++){
            result += plain[i];
        }
        if (op == 1){
            LOG(result);
        }
    } else if (mode == 3){

        LOG("File Read Complete...");
        P3DES *d3 = new P3DES(k1, k2, k3, threads, size, 1);
        string *enc = new string[size];

        LOG("Encrypting...");
        enc = d3->pEncryptSbox(data);
        writeFileStr("enc.txt", enc, size);

        LOG("Decrypting...");
        P3DES *d3_2 = new P3DES(k1, k2, k3, threads, size, 1);
        string *plain = new string[size];
        plain = d3_2->pDecryptSbox(enc);

        string result = "";
        for (int i = 0; i < size; i++){
            result += plain[i];
        }
        if (op == 1){
            LOG(result);
        }
    } else if (mode == 4){

        LOG("File Read Complete...");
        P3DES *d3 = new P3DES(k1, k2, k3, threads, size, 1);
        string *enc = new string[size];

        LOG("Encrypting...");
        enc = d3->pEncryptNested(data);
        writeFileStr("enc.txt", enc, size);

        LOG("Decrypting...");
        P3DES *d3_2 = new P3DES(k1, k2, k3, threads, size, 1);
        string *plain = new string[size];
        plain = d3_2->pDecryptNested(enc);

        string result = "";
        for (int i = 0; i < size; i++){
            result += plain[i];
        }
        if (op == 1){
            LOG(result);
        }
    } else {
        cout << "Something went wrong!" << endl;
    }
}