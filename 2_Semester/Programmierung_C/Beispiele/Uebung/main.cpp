//
// Created by Korbinian on 08.06.2024.
//
#include<iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv){
    string s;
    cin >> s;
    int spaces=0;
    for(char c: s){
        if(reinterpret_cast<const char *>(c) == " "){
            spaces++;
        }
    }
    cout << endl << spaces;
}
