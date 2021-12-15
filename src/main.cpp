#include <iostream>
#include <string>
#include <vector>
#include "Serial.h"

using namespace std;

int main(){
    SerialDES *sd = new SerialDES(key);
    vector<string> genKeys = sd->generateKeys();
    // for (int i = 0; i < genKeys.size(); i++){
    //     cout << genKeys[i] << endl;
    // }

    vector<string> text = readFile("input.txt");
    cout << "Input: ";
    for (int i = 0; i < text.size(); i++){
        cout << text[i] << endl;
    }
    vector<string> cipherText;
    string cipher[text.size()];
    for (int i = 0; i < text.size(); i++){
        cipher[i] = sd->encrypt(text[i], genKeys);
    }

    cout << "Encrypted: " << cipher << endl;
    for (int i = 0; i < text.size(); i++){
        cipherText.push_back(cipher[i]);
    }

    writeFile("enc.txt", cipherText);

    for (int i = 0; i < cipherText.size(); i++){
		cout << "Encrypted: " << cipherText[i] << endl;
	}

    reverse(genKeys.begin(), genKeys.end());
    string decrypted;
    string dec[cipherText.size()];
    for (int i = 0; i < cipherText.size(); i++){
        dec[i] = sd->encrypt(cipherText[i], genKeys);
    }

    for (int i = 0; i < cipherText.size(); i++){
        decrypted += dec[i];
    }

    cout << "Decrypted: " << decrypted << endl;
}