#include <iostream>
#include <string>
#include <vector>
#include "Serial.h"
#include "misc.h"

using namespace std;

int main(){
    // SerialDES *sd = new SerialDES(19, "Ali");
    // sd->printInfo();

    vector<string> input = readFile("input.txt");
    for (int i = 0; i < input.size(); i++){
        cout << input[i] << endl;
    }
}