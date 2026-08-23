#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;


vector<uint8_t> biteTobyte(const string& filePath){
    ifstream file(filePath, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file '" << filePath << "'" << endl;
        return {};
    }

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        cerr << "Error: Failed to read file data." << endl;
        return {};
    }

    return buffer;
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
    int i = 0;

    while (x > 0)
    {
        o.push_back((x % 2));
        x = x / 2;
    }
    reverse(o.begin(), o.end());
    while (o.size() < 8)
    {
        o.insert(o.begin(), 0);
    }
    return o;
}


void Image_Encode(string s){
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<uint8_t> byte = biteTobyte(s);
    vector<int> v;
    for (int i = 0; i < byte.size(); i++)
    {
        int x = (int)byte[i];
        vector<int> z = bin(x);
        for (int j = 0; j < z.size(); j++) {
            v.push_back(z[j]);
        }
    }


    int originalSize = byte.size();
    for (int i = 0; i < v.size(); i += 6) {

    vector<int> pack;

    for (int j = i; j < i + 6; j++) {
        if (j < v.size())
            pack.push_back(v[j]);
        else
            pack.push_back(0);
    }

    int result = convert(pack);
    cout << alphabet[result];
        }

    if (originalSize % 3 == 1) {
        cout << "==";
    }
    else if (originalSize % 3 == 2) {
        cout << "=";
    }

    cout << endl;
    
    
}




int main(){
    string image;
    getline(cin,image); 

    Image_Encode(image);

    
}