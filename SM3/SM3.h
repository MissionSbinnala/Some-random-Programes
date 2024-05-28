#pragma once
#include<iostream>
#include<bitset>
#include<vector>
#include<string>
#define Byte bitset<8>
#define DWord bitset<32>

using std::string, std::bitset, std::vector, std::cout, std::cin, std::endl;

class Message {
public:
	Message(string s);
	void DisplayVector();
	void SM3();
	vector<Byte> stream;
private:
	DWord W[68], WDot[64];
	DWord Vector[8];
	DWord A, B, C, D, E, F, G, H;
	void Padding();
	void Merge(int n);
	void WExpension();
	DWord P1(DWord w);
	DWord P0(DWord w);
	DWord FF1(DWord x, DWord y, DWord z);
	DWord FF2(DWord x, DWord y, DWord z);
	DWord GG2(DWord x, DWord y, DWord z);
	void CompressFunction();
};