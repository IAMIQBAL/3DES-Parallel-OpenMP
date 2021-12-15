#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

string leftShift(int nshifts, string input){
    string tmp = "";
    for (int i = 0; i < nshifts; i++){
        for (int j = 1; j < 28; j++){
            tmp += input[j];
        }
        tmp += input[0];
        input = tmp;
        tmp = "";
    }
    return input;
}

string opXOR(string inp1, string inp2){
    string tmp = "";
    for (int i = 0; i < inp1.size(); i++){
        if (inp1[i] == inp2[i]){
            tmp += "0";
        } else {
            tmp += "1";
        }
    }
    return tmp;
}

string permutation(int *arr, int size, string input){
    string tmp = "";
    for (int i = 0; i < size; i++){
        tmp += input[arr[i] - 1];
    }
    return tmp;
}

string hexToBin(string input){
    string bin = "";
    for (int i = 0; i < input.size(); i++){
        switch (input[i]){
            case '0': bin += "0000"; break;
            case '1': bin += "0001"; break;
            case '2': bin += "0010"; break;
            case '3': bin += "0011"; break;
            case '4': bin += "0100"; break;
            case '5': bin += "0101"; break;
            case '6': bin += "0110"; break;
            case '7': bin += "0111"; break;
            case '8': bin += "1000"; break;
            case '9': bin += "1001"; break;
            case 'A':
            case 'a': bin += "1010"; break;
            case 'B':
            case 'b': bin += "1011"; break;
            case 'C':
            case 'c': bin += "1100"; break;
            case 'D':
            case 'd': bin += "1101"; break;
            case 'E':
            case 'e': bin += "1110"; break;
            case 'F':
            case 'f': bin += "1111"; break;
        }
    }
    return bin;
}

string decToBin(int input){
    string bin = "";
    while (input > 0){
        bin = (char)(input % 2 + '0') + bin;
        input /= 2;
    }
    while (bin.size() < 4){
        bin = '0' + bin;
    }
    return bin;
}

string strToBin(string input){
    string bin = "";
    for (int i = 0; i < input.length(); i++){
        bin += bitset<8>(input[i]).to_string();
    }
    return bin;
}

string binToStr(string input){
    string tmp = "";
    for (int i = 0; i < input.length(); i+=8){
        string bin = input.substr(i, 8);
        char t = static_cast<char>(bitset<8>(bin.substr(0, 8)).to_ulong());
        tmp += t;
    }
    return tmp;
}

vector<string> readFile(string fName){
    string tmp, data;
    vector<string> dataVec;
    ifstream input(fName);
    while (getline(input, tmp)){
        data += tmp;
    }

    while (data.length() % 8 != 0){
        data += " ";
    }

    for (int i = 0; i < data.length(); i += 8){
        dataVec.push_back(data.substr(i, 8));
    }
    input.close();
    return dataVec;
}

void writeFile(string fName, vector<string> data){
    ofstream output;
    output.open(fName, ios::app);
    for (int i = 0; i < data.size(); i++){
        output << data[i];
    }
    output.close();
}