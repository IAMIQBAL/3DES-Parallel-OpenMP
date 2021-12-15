#include <iostream>
#include <vector>
#include <string>
#include "Serial.h"
#include <omp.h>

using namespace std;

class Parallel {
private:
    string key;
    SerialDES *sd;
public:

    Parallel(string key){
        this->key = key;
        sd = new SerialDES(key);
    };

    vector<string> pGenerateKeys(){
        return sd->generateKeys();
    }

    string* pEncrypt(vector<string> text, vector<string> genKeys){
        string *output = new string[text.size()];
        #pragma omp parallel for schedule(dynamic) num_threads(8)
        for (int i = 0; i < text.size(); i++){
            output[i] = sd->encrypt(text[i], genKeys);
        }
        return output;
    }
};