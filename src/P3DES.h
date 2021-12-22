#include <iostream>
#include <vector>
#include <string>
#include "S3DES.h"

using namespace std;

class P3DES {
private:
    string k1;
    string k2;
    string k3;
    int nThreads;
    DES *d1;
    DES *d2;
    DES *d3;
    SboxParallel *sd1;
    SboxParallel *sd2;
    SboxParallel *sd3;
    int len;
    vector<string> genK1;
    vector<string> genK2;
    vector<string> genK3;
    double encTimeParallel;
    double encTimeSParallel;
    double encTimeNParallel;

public:

    P3DES(string k1, string k2, string k3, int nThreads, int len, int mod){
        this->k1 = k1;
        this->k2 = k2;
        this->k3 = k3;
        this->nThreads = nThreads;
        this->len = len;
        if (mod == 0){
            d1 = new DES(k1);
            d2 = new DES(k2);
            d3 = new DES(k3);
            genK1 = d1->generateKeys(); // Encrypt
            genK2 = d2->generateKeys(); // Decrypt
            genK3 = d3->generateKeys(); // Encrypt
        } else if (mod == 1){
            sd1 = new SboxParallel(k1, nThreads);
            sd2 = new SboxParallel(k2, nThreads);
            sd3 = new SboxParallel(k3, nThreads);
            genK1 = sd1->generateKeys(); // Encrypt
            genK2 = sd2->generateKeys(); // Decrypt
            genK3 = sd3->generateKeys(); // Encrypt
        }
    };

    string* pEncrypt(string* text){

        reverse(genK2.begin(), genK2.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s1[i] = d1->encrypt(text[i], genK1);
        }

        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s2[i] = d2->encrypt(s1[i], genK2);
        }

        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s3[i] = d3->encrypt(s2[i], genK3);
        }
	    double t2 = omp_get_wtime();
        cout << "Parallel Encryption Time: " << (t2 - t1) << "s" << endl;

        encTimeParallel = t2-t1;
        return s3;
    }

    string* pDecrypt(string *text){

        reverse(genK1.begin(), genK1.end());
        reverse(genK3.begin(), genK3.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s1[i] = d1->encrypt(text[i], genK3);
        }

        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s2[i] = d2->encrypt(s1[i], genK2);
        }

        #pragma omp parallel for schedule(dynamic) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s3[i] = d3->encrypt(s2[i], genK1);
        }
	    double t2 = omp_get_wtime();
        cout << "Parallel Decryption Time: " << (t2 - t1) << "s" << endl;

        return s3;
    }

    string* pEncryptSbox(string* text){

        reverse(genK2.begin(), genK2.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        for (int i = 0; i < len; i++){
            s1[i] = sd1->encrypt(text[i], genK1);
        }

        for (int i = 0; i < len; i++){
            s2[i] = sd2->encrypt(s1[i], genK2);
        }

        for (int i = 0; i < len; i++){
            s3[i] = sd3->encrypt(s2[i], genK3);
        }
	    double t2 = omp_get_wtime();
        cout << "Parallel SBOX Encryption Time: " << (t2 - t1) << "s" << endl;
        
        encTimeSParallel = t2 - t1;
        return s3;
    }

    string* pDecryptSbox(string *text){

        reverse(genK1.begin(), genK1.end());
        reverse(genK3.begin(), genK3.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        for (int i = 0; i < len; i++){
            s1[i] = sd1->encrypt(text[i], genK3);
        }

        for (int i = 0; i < len; i++){
            s2[i] = sd2->encrypt(s1[i], genK2);
        }

        for (int i = 0; i < len; i++){
            s3[i] = sd3->encrypt(s2[i], genK1);
        }
	    double t2 = omp_get_wtime();
        cout << "Parallel SBOX Decryption Time: " << (t2 - t1) << "s" << endl;

        return s3;
    }

    string* pEncryptNested(string* text){

        reverse(genK2.begin(), genK2.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s1[i] = sd1->encrypt(text[i], genK1);
        }

        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s2[i] = sd2->encrypt(s1[i], genK2);
        }

        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s3[i] = sd3->encrypt(s2[i], genK3);
        }
	    double t2 = omp_get_wtime();
        cout << "Nested Parallel Encryption Time: " << (t2 - t1) << "s" << endl;

        encTimeNParallel = t2 - t1;
        return s3;
    }

    string* pDecryptNested(string *text){

        reverse(genK1.begin(), genK1.end());
        reverse(genK3.begin(), genK3.end());

        string *s1 = new string[len];
        string *s2 = new string[len];
        string *s3 = new string[len];

	    double t1 = omp_get_wtime();
        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s1[i] = sd1->encrypt(text[i], genK3);
        }

        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s2[i] = sd2->encrypt(s1[i], genK2);
        }

        omp_set_nested(1);
        #pragma omp parallel for schedule(guided) num_threads(nThreads)
        for (int i = 0; i < len; i++){
            s3[i] = sd3->encrypt(s2[i], genK1);
        }
	    double t2 = omp_get_wtime();
        cout << "Nested Parallel Decryption Time: " << (t2 - t1) << "s" << endl;

        return s3;
    }

    double getPEncTime(){
        return encTimeParallel;
    }

    double getSEncTime(){
        return encTimeSParallel;
    }

    double getNEncTime(){
        return encTimeNParallel;
    }
};