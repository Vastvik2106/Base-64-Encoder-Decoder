#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <termios.h>
#include <unistd.h>
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

int convert(vector<int> digits){
    int ans = 0;
    for (int i = 0; i < digits.size(); i++) {
        ans = ans * 2 + digits[i];
    }
    return ans;
}

vector<int> bin(int x){
    vector<int> o;
    while (x > 0) {
        o.push_back((x % 2));
        x = x / 2;
    }
    reverse(o.begin(), o.end());
    while (o.size() < 6) {
        o.insert(o.begin(), 0);
    }
    return o;
}

void Image_Decode(string s){
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
        return isspace(c);
    }), s.end());

    while (!s.empty() && s.back() == '=') {
        s.pop_back();
    }

    vector<int> v;
    for (int i = 0; i < (int)s.size(); i++) {
        int x = alphabet.find(s[i]);
        if (x == (int)string::npos) {
            cerr << "Error: Invalid Base64 character." << endl;
            return;
        }
        vector<int> z = bin(x);
        for (int j = 0; j < (int)z.size(); j++) v.push_back(z[j]);
    }

    vector<uint8_t> byte;
    for (int i = 0; i + 8 <= (int)v.size(); i += 8){
        vector<int> pack(v.begin() + i, v.begin() + i + 8);
        byte.push_back((uint8_t)convert(pack));
    }

    ofstream file("decoded_image.jpg", ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not create decoded image." << endl;
        return;
    }
    file.write(reinterpret_cast<char*>(byte.data()), byte.size());
    if (!file) {
        cerr << "Error: Failed to write image data." << endl;
        return;
    }
    file.close();
    cout << "Image decoded successfully." << endl;
}

int main(){
    cout << "Enter the Base64 code to decode: " << endl;
    string image = Raa();
    Image_Decode(image);
}