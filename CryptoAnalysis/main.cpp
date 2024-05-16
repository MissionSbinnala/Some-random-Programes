#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


int main() {
	int distribution[26];
	string crypto;
	cin >> crypto;
	for (int i = 0; i < 26; i++) {
		distribution[i] = 0;
	}
	for (int i = 0; i < crypto.length(); i++) {
		if (crypto[i] < 94) {
			crypto[i] = crypto[i] + 32;
		}
		if (crypto[i] == 'a') {
			distribution[0]++;
		}
		if (crypto[i] == 'b') {
			distribution[1]++;
		}
		if (crypto[i] == 'c') {
			distribution[2]++;
		}
		if (crypto[i] == 'd') {
			distribution[3]++;
		}
		if (crypto[i] == 'e') {
			distribution[4]++;
		}
		if (crypto[i] == 'f') {
			distribution[5]++;
		}
		if (crypto[i] == 'g') {
			distribution[6]++;
		}
		if (crypto[i] == 'h') {
			distribution[7]++;
		}
		if (crypto[i] == 'i') {
			distribution[8]++;
		}
		if (crypto[i] == 'j') {
			distribution[9]++;
		}
		if (crypto[i] == 'k') {
			distribution[10]++;
		}
		if (crypto[i] == 'l') {
			distribution[11]++;
		}
		if (crypto[i] == 'm') {
			distribution[12]++;
		}
		if (crypto[i] == 'n') {
			distribution[13]++;
		}
		if (crypto[i] == 'o') {
			distribution[14]++;
		}
		if (crypto[i] == 'p') {
			distribution[15]++;
		}
		if (crypto[i] == 'q') {
			distribution[16]++;
		}
		if (crypto[i] == 'r') {
			distribution[17]++;
		}
		if (crypto[i] == 's') {
			distribution[18]++;
		}
		if (crypto[i] == 't') {
			distribution[19]++;
		}
		if (crypto[i] == 'u') {
			distribution[20]++;
		}
		if (crypto[i] == 'v') {
			distribution[21]++;
		}
		if (crypto[i] == 'w') {
			distribution[22]++;
		}
		if (crypto[i] == 'x') {
			distribution[23]++;
		}
		if (crypto[i] == 'y') {
			distribution[24]++;
		}
		if (crypto[i] == 'z') {
			distribution[25]++;
		}
	}
	cout <<"a\t" << distribution[0]<<"\t";
	cout <<"b\t" << distribution[1]<<"\t";
	cout <<"c\t" << distribution[2]<<"\t";
	cout <<"d\t" << distribution[3]<<"\t";
	cout <<"e\t" << distribution[4]<<"\t" << endl;
	cout <<"f\t" << distribution[5]<<"\t";
	cout <<"g\t" << distribution[6]<<"\t";
	cout <<"h\t" << distribution[7]<<"\t";
	cout <<"i\t" << distribution[8]<<"\t";
	cout <<"j\t" << distribution[9]<<"\t" << endl;
	cout <<"k\t" << distribution[10]<<"\t";
	cout <<"l\t" << distribution[11]<<"\t";
	cout <<"m\t" << distribution[12]<<"\t";
	cout <<"n\t" << distribution[13]<<"\t";
	cout <<"o\t" << distribution[14]<<"\t" << endl;
	cout <<"p\t" << distribution[15]<<"\t";
	cout <<"q\t" << distribution[16]<<"\t";
	cout <<"r\t" << distribution[17]<<"\t";
	cout <<"s\t" << distribution[18]<<"\t";
	cout <<"t\t" << distribution[19]<<"\t" << endl;
	cout <<"u\t" << distribution[20]<<"\t";
	cout <<"v\t" << distribution[21]<<"\t";
	cout <<"w\t" << distribution[22]<<"\t";
	cout <<"x\t" << distribution[23]<<"\t";
	cout <<"y\t" << distribution[24]<<"\t" << endl;
	cout <<"z\t" << distribution[25]<<"\t" << endl;
	system("pause");
}