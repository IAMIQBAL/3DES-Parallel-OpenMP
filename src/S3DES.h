#include <iostream>
#include <vector>
#include <string>
#include "SboxParallel.h"

using namespace std;

class S3DES {
private:
    string k1;
    string k2;
    string k3;
    DES *d1;
    DES *d2;
    DES *d3;
    int len;
    vector<string> genK1;
    vector<string> genK2;
    vector<string> genK3;
    double encTime;

public:

    S3DES(string k1, string k2, string k3, int len){
        this->k1 = k1;
        this->k2 = k2;
        this->k3 = k3;
        this->len = len;
        d1 = new DES(k1);
        d2 = new DES(k2);
        d3 = new DES(k3);

        genK1 = d1->generateKeys(); // Encrypt
        genK2 = d2->generateKeys(); // Decrypt
        genK3 = d3->generateKeys(); // Encrypt
    };

    string* pEncrypt(string* text){

        reverse(genK2.begin(), genK2.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        for (int i = 0; i < len; i++){
            s1[i] = d1->encrypt(text[i], genK1);
        }

        for (int i = 0; i < len; i++){
            s2[i] = d2->encrypt(s1[i], genK2);
        }

        for (int i = 0; i < len; i++){
            s3[i] = d3->encrypt(s2[i], genK3);
        }
	    double t2 = omp_get_wtime();
        cout << "Serial Encryption Time: " << (t2 - t1) << "s" << endl;

        encTime = t2 - t1;
        return s3;
    }

    string* pDecrypt(string *text){

        reverse(genK1.begin(), genK1.end());
        reverse(genK3.begin(), genK3.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        for (int i = 0; i < len; i++){
            s1[i] = d1->encrypt(text[i], genK3);
        }

        for (int i = 0; i < len; i++){
            s2[i] = d2->encrypt(s1[i], genK2);
        }

        for (int i = 0; i < len; i++){
            s3[i] = d3->encrypt(s2[i], genK1);
        }
	    double t2 = omp_get_wtime();
        cout << "Serial Decryption Time: " << (t2 - t1) << "s" << endl;

        return s3;
    }

    double getEncTime(){
        return encTime;
    }
};