#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <limits>
#include "Vortex.h"
using namespace std;



int main(){
    cout << "=============================\n";
    cout << "         VORTEX64\n";
    cout << "=============================\n\n";

    cout << "1. Encode Text\n";
    cout << "2. Decode Text\n";
    cout << "3. Encode Image\n";
    cout << "4. Decode Image\n";
    cout << "5. Exit\n\n";

    int choice;

    cout << "Choose an option: ";
    cin >> choice;  

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(choice) {
    case 1:{
        cout << "Text Encoder selected\n";
         string text;
        cout << "Enter text: ";
        getline(cin, text);
        Encode(text);
        break;
    }
    case 2:{
        cout << "Text Decoder selected\n";
        string decosion;
        cout << "Enter Base64: ";
        getline(cin, decosion);
        Decode(decosion);
        break;
    }
    case 3:{
    cout << "Image Encoder selected\n";
    string image;
    string output;
    cout << "Enter image path: ";
    getline(cin, image);
    cout << "Enter output Base64 file: ";
    getline(cin, output);
    Image_Encode(image, output);
    break;
    }   
    case 4:{
    cout << "Image Decoder selected\n";
    string input;
    string output;
    cout << "Enter Base64 file: ";
    getline(cin, input);
    cout << "Enter output image path: ";
    getline(cin, output);
    Image_Decode(input, output);   
    break;
    }
    case 5:{
        choice==5;
        cout << "Goodbye!\n";
        return 0;
    }

    default:{
        cout << "Invalid option!\n";
    }

    }





}