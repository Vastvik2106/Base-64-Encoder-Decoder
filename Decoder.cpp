#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int final(vector<long long>&v){
    int ans = 0;
    int j = 0;
    for(int i=v.size()-1; i>=0; i--){
        ans = ans + (v[i]*pow(2,j));
        j++;
    }

    return ans;

}



void  bin(vector<int>&v){
    vector<long long> temp;
    for(int i=0; i<v.size();i++){
        int yum = v[i];
        
        vector<long long>aisa;
        while(yum>0){
            aisa.push_back(yum%2);
            yum = yum/2;               
        }

        while(aisa.size()<6){
            aisa.push_back(0);
        }
        for(int i=0; i<aisa.size();i++){
            temp.push_back(aisa[aisa.size()-1-i]);
        }       
    }
    for (int i = 0; i + 8 <= (int)temp.size(); i += 8) {
        vector<long long> ouu(temp.begin() + i, temp.begin() + i + 8);
        int result = final(ouu);
        cout<<(char)result;
    }
    cout<<endl;
    
}



void Decode(string s){
    while (!s.empty() && s.back() == '=') {     
        s.pop_back();
    }
    vector<int>v;
    vector<string>o;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for(int i=0; i<s.size();i++){
        int value = alphabet.find(s[i]);
        if (value == (int)string::npos) {    
            cerr << "Error: Invalid Base64 character." << endl;
            return;
        }
        v.push_back(value);
    }
    
    bin(v);

}


int main(){
    string s;
    getline(cin,s);

    Decode(s);

}