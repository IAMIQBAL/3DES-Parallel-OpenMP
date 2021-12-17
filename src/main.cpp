#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include "P3DES.h"
// #include "S3DES.h"

using namespace std;

int main(){

    // 3DES Parallel
    int threads = 8;
    string fName = "../tests/plaintext.txt";
    vector<string> text = readFile(fName);
    int size = text.size();
    string* data = new string[size];
    for (int i = 0; i < size; i++){
        data[i] = text[i];
        // cout << data[i];
    }
    // cout << endl;
    

    string k1 = "ABC12532110EDA56";
    string k2 = "ABC12532110EDA57";
    string k3 = "ABC12532110EDA90";
    cout << "File Read Complete..." << endl;
    P3DES *d3 = new P3DES(k1, k2, k3, threads, size, 1);
    string *enc = new string[size];
    enc = d3->pEncryptNested(data);
    writeFileStr("enc.txt", enc, size);

    cout << "Decrypted " << endl;
    P3DES *d3_2 = new P3DES(k1, k2, k3, threads, size, 1);
    string *plain = new string[size];
    plain = d3_2->pDecryptNested(enc);

    string result = "";
    for (int i = 0; i < size; i++){
        result += plain[i];
    }
    cout << result;
    cout << endl;

    // 3DES Serial
    // string fName = "../tests/bible.txt";
    // vector<string> text = readFile(fName);
    // int size = text.size();
    // string* data = new string[size];
    // for (int i = 0; i < size; i++){
    //     data[i] = text[i];
    //     // cout << data[i];
    // }
    // // cout << endl;
    

    // string k1 = "ABC12532110EDA56";
    // string k2 = "ABC12532110EDA57";
    // string k3 = "ABC12532110EDA90";
    // cout << "File Read Complete..." << endl;
    // S3DES *d3 = new S3DES(k1, k2, k3, size);
    // string *enc = new string[size];
    // enc = d3->pEncrypt(data);
    // writeFileStr("enc.txt", enc, size);

    // cout << "Decrypted " << endl;
    // S3DES *d3_2 = new S3DES(k1, k2, k3, size);
    // string *plain = new string[size];
    // plain = d3_2->pDecrypt(enc);

    // string result = "";
    // for (int i = 0; i < size; i++){
    //     result += plain[i];
    // }
    // cout << result;
    // cout << endl;
}