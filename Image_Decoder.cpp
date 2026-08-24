#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include "Vortex.h"
#include <sstream>
using namespace std;

string Raa(){
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string input;
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n' || c == '\r') break;
        input += c;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
    return input;
}



void Image_Decode(string inputPath, string output){
    ifstream in(inputPath);
    if (!in.is_open()) {
        cerr << "Error: Could not open Base64 file '" << inputPath << "'" << endl;
        return;
    }
    stringstream buf;
    buf << in.rdbuf();
    string s = buf.str();

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
        return isspace(c);
    }), s.end());

    int padding = 0;
    if (!s.empty() && s.back() == '=') padding++;
    if (s.size() >= 2 && s[s.size() - 2] == '=') padding++;

    vector<int> v;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '=') continue;
        int x = alphabet.find(s[i]);
        if (x == (int)string::npos) {
            cerr << "Error: Invalid Base64 character." << endl;
            return;
        }
        vector<int> z = bin(x);
        for (int j = 0; j < (int)z.size(); j++) v.push_back(z[j]);
    }

    vector<uint8_t> byte;
    int validBytes = (v.size() / 8);   

    for (int i = 0; i < validBytes * 8; i += 8) {
        vector<int> pack(v.begin() + i, v.begin() + i + 8);
        byte.push_back((uint8_t)convert(pack));
    }

    ofstream file(output, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not create output image." << endl;
        return;
    }
    file.write(reinterpret_cast<char*>(byte.data()), byte.size());
    file.close();

    cout << "Image decoded successfully." << endl;
    cout << "Image saved to: " << output << endl;
}

