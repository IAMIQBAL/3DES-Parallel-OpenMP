#include "matplotlibcpp.h"
#include "P3DES.h"
#include <vector>

using namespace std;
namespace plt = matplotlibcpp;

void getPlot(vector<double> x1, vector<double> x2,
            vector<double> x3, vector<double> x4, 
            vector<double> y1,
            int threads = 0){

    // plt::xkcd();
    plt::plot(x1, y1);
    plt::plot(x2, y1);
    plt::plot(x3, y1);
    plt::plot(x4, y1);

    plt::xlabel("Time");
    plt::ylabel("File size (bytes)");
    if (threads == 0){
        plt::title("Serial Execution");
    } else {
        plt::title("Threads = " + to_string(threads) + "\nB = Serial, Y = Parallel, G = Sbox, R = Nested");
    }
    plt::show();
}

void getStats(string* files, int size,
            vector<double>& X1, vector<double>& X2,
            vector<double>& X3, vector<double>& X4,
            vector<double>& Y1, int threads){
    // X = time
    // Y = file size
    // Title = num of threads
    for (int i = 0; i < size; i++){
        Y1.push_back(getFileSize(files[i]));
        // Y2.push_back(getFileSize(files[i]));
    }


    // Serial
    for (int i = 0; i < size; i++){
        vector<string> text = readFile(files[i]);
        int len = text.size();
        string* data = new string[len];
        for (int i = 0; i < len; i++){
            data[i] = text[i];
        }
        S3DES *serial = new S3DES(Key1, Key2, Key3, len);
        serial->pEncrypt(data);
        X1.push_back(serial->getEncTime());
    }

    // Parallel
    for (int i = 0; i < size; i++){
        vector<string> text = readFile(files[i]);
        int len = text.size();
        string* data = new string[len];
        for (int i = 0; i < len; i++){
            data[i] = text[i];
        }
        P3DES *parallel = new P3DES(Key1, Key2, Key3, threads, len, 0);
        parallel->pEncrypt(data);
        X2.push_back(parallel->getPEncTime());
    }

    // Sbox Parallel
    for (int i = 0; i < size; i++){
        vector<string> text = readFile(files[i]);
        int len = text.size();
        string* data = new string[len];
        for (int i = 0; i < len; i++){
            data[i] = text[i];
        }
        P3DES *parallel = new P3DES(Key1, Key2, Key3, threads, len, 1);
        parallel->pEncryptSbox(data);
        X3.push_back(parallel->getSEncTime());
    }

    // Nested Parallel
    for (int i = 0; i < size; i++){
        vector<string> text = readFile(files[i]);
        int len = text.size();
        string* data = new string[len];
        for (int i = 0; i < len; i++){
            data[i] = text[i];
        }
        P3DES *parallel = new P3DES(Key1, Key2, Key3, threads, len, 1);
        parallel->pEncryptNested(data);
        X4.push_back(parallel->getNEncTime());
    }

    for (int i = 0; i < size; i++){
        cout << Y1[i] << endl;
        // cout << Y2[i] << endl;
    }
}

// void fill(vector<double>& x, int &time){
//     for (int i = 0; i <5; i++){
//         x.push_back(i);
//     }
//     time = 50;
// }

int main() {

    vector<double> X1;
    vector<double> X2;
    vector<double> X3;
    vector<double> X4;
    vector<double> Y1;
    // vector<double> Y2;
    int size = 4;

    string *files = new string[size];
    files[0] = "../tests/AliBaba.txt";
    files[1] = "../tests/plrabn12.txt";
    files[2] = "../tests/sherlock.txt";
    files[3] = "../tests/TheSnowqueen.txt";

    cout << "Threads: ";
    int threads = 0;
    cin >> threads;

    getStats(files, size, X1, X2, X3, X4, Y1, threads);
    
    getPlot(X1, X2, X3, X4, Y1, threads);
}