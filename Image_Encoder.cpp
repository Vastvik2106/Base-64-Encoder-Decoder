#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Vortex.h"

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


void Image_Encode(string inputPath, string outputPath){

    string alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vector<uint8_t> byte = biteTobyte(inputPath);

    if (byte.empty()) {
        cerr << "Error: Image contains no data or could not be read." << endl;
        return;
    }

    vector<int> v;

    for (int i = 0; i < byte.size(); i++) {

        int x = (int)byte[i];

        vector<int> z = bin(x);

        for (int j = 0; j < z.size(); j++) {
            v.push_back(z[j]);
        }
    }


    int originalSize = byte.size();


    ofstream output(outputPath);

    if (!output.is_open()) {
        cerr << "Error: Could not create output file '"
             << outputPath << "'" << endl;
        return;
    }

    for (int i = 0; i < v.size(); i += 6) {

        vector<int> pack;

        for (int j = i; j < i + 6; j++) {

            if (j < v.size())
                pack.push_back(v[j]);
            else
                pack.push_back(0);
        }

        int result = convert(pack);

        output << alphabet[result];
    }

    if (originalSize % 3 == 1) {
        output << "==";
    }
    else if (originalSize % 3 == 2) {
        output << "=";
    }

    output << '\n';

    output.close();

    cout << "Image encoded successfully!" << endl;
    cout << "Base64 saved to: " << outputPath << endl;
}