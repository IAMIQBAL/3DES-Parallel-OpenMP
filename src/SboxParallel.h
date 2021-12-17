#include <iostream>
#include <string>
#include <vector>
#include "DES.h"
#include <omp.h>

using namespace std;

class SboxParallel {
private:
    string key; // 64 bit key
    int threads;

public:
    SboxParallel(string key, int threads){
        this->key = key;
        this->threads = threads;
    }

    vector<string> generateKeys(){
        key = hexToBin(key);
        key = permutation(pc1, 56, key);

        string k1 = key.substr(0, 28);
        string k2 = key.substr(28, 28);

        vector<string> genKeys;
        for (int i = 0; i < 16; i++){
            k1 = leftShift(bitRot[i], k1);
            k2 = leftShift(bitRot[i], k2);
            genKeys.push_back(permutation(pc2, 48, k1 + k2));
        }
        return genKeys;
    }

    string encrypt(string text, vector<string> genKeys){
        text = strToBin(text);

        text = permutation(ip, 64, text); // Initial permutation
        string left = text.substr(0, 32);
        string right = text.substr(32, 32);

        for (int i = 0; i < 16; i++){
            string expansionP = permutation(dBox, 48, right);
            string XOR = opXOR(genKeys[i], expansionP);

            string sbOut[8];
            string output = "";
            int *x = new int[8];
            int *y = new int[8];
            int *z = new int[8];

            #pragma omp parallel for num_threads(threads) schedule(static)
            for (int i = 0; i < 8; i++){
                int tid = omp_get_thread_num();
                x[tid] = 2 * int(XOR[tid * 6] - '0') + int(XOR[tid * 6 + 5] - '0'); 
                y[tid] = 8 * int(XOR[tid * 6 + 1] - '0') + 4 * int(XOR[tid * 6 + 2] - '0') + 2 * int(XOR[tid * 6 + 3] - '0') + int(XOR[tid * 6 + 4] - '0');
                z[tid] = sBox[tid][x[tid]][y[tid]];
                sbOut[tid] = decToBin(z[tid]);
            }
            for (int i = 0; i < 8; i++) output += sbOut[i];
            output = permutation(pbox, 32, output);
            XOR = opXOR(output, left);
            left = XOR;
            if (i != 15){
                swap(left, right);
            }
        }
        string combined = left + right;
        string encrypted = binToStr(permutation(ipInv, 64, combined));
        return encrypted;
    }
};