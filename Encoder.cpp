#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

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

void Encode(string s)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    vector<int> v;
    for (int i = 0; i < s.size(); i++)
    {
        int x = (int)(unsigned char)s[i];
        vector<int> z = bin(x);
        for (int j = 0; j < z.size(); j++) {
            v.push_back(z[j]);
        }
    }
    int originalSize = s.size();
    while (v.size() % 6 != 0){
        v.push_back(0);
    }

    for (int i = 0; i < v.size(); i += 6) {
        vector<int> pack(v.begin() + i, v.begin() + i + 6);
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

int main()
{
    string s;
    getline(cin, s);

    Encode(s);
}