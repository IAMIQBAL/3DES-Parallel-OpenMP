#include <iostream>
#include <string>
#include <vector>
// #include "Serial.h"
#include "Parallel.h"

using namespace std;

int main(){

    // Serial

    // SerialDES *sd = new SerialDES(key);
    // vector<string> genKeys = sd->generateKeys();
    string fName = "../tests/plaintext.txt";

    vector<string> text = readFile(fName);
    // cout << "Input: ";
    // for (int i = 0; i < text.size(); i++){
    //     cout << text[i] << endl;
    // }
    vector<string> cipherText;
    string *cipher = new string[text.size()];
    // for (int i = 0; i < text.size(); i++){
    //     cipher[i] = sd->encrypt(text[i], genKeys);
    // }

    // cout << "Encrypted: " << cipher << endl;
    // for (int i = 0; i < text.size(); i++){
    //     cipherText.push_back(cipher[i]);
    // }

    // writeFile("enc.txt", cipherText);

    // for (int i = 0; i < cipherText.size(); i++){
	// 	cout << "Encrypted: " << cipherText[i] << endl;
	// }

    // reverse(genKeys.begin(), genKeys.end());
    // string decrypted;
    // string dec[cipherText.size()];
    // for (int i = 0; i < cipherText.size(); i++){
    //     dec[i] = sd->encrypt(cipherText[i], genKeys);
    // }

    // for (int i = 0; i < cipherText.size(); i++){
    //     decrypted += dec[i];
    // }

    // cout << "Decrypted: " << decrypted << endl;

    // Parallel

    // Parallel *pd = new Parallel(key);
    // vector<string> genKeys = pd->pGenerateKeys();

	// double Et1 = omp_get_wtime();
    // cipher = pd->pEncrypt(text, genKeys);
	// double Et2 = omp_get_wtime();

    // for (int i = 0; i < text.size(); i++){
    //     cipherText.push_back(cipher[i]);
    // }

    // writeFile("enc.txt", cipherText);

    // reverse(genKeys.begin(), genKeys.end());
    // string decrypted;
    // string *dec = new string[cipherText.size()];

	// double Dt1 = omp_get_wtime();
    // dec = pd->pEncrypt(cipherText, genKeys);
	// double Dt2 = omp_get_wtime();

    // for (int i = 0; i < cipherText.size(); i++){
    //     decrypted += dec[i];
    // }

    // // cout << "Decrypted: " << decrypted << endl;
	// cout << "Encryption Time taken:" << (Et2 - Et1) << "s" << endl;
	// cout << "Decryption Time taken:" << (Dt2 - Dt1) << "s" << endl;
}