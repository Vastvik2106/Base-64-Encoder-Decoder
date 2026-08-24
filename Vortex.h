#ifndef VORTEX_H
#define VORTEX_H
#include <string>
#include <vector>
using namespace std;

int convert(std::vector<int> digits);
vector<int> bin(int x);

void Encode(string s);
void Decode(string s);
void Image_Encode(string inputPath, string outputPath);
void Image_Decode(string s, string outputPath);

#endif