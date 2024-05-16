#include <iostream>
#include <numeric>
#include <vector>
#include <stdlib.h>
#include<string>

using namespace std;

vector<int> Numberlize(string string) {
	vector<int> stringNum;
	for (int i = 0; i < string.size(); i++) {
		stringNum.push_back(string[i] - 97);
		cout << stringNum[i] << " ";
	}
	return stringNum;
}

string Stringlize(vector<int> stringNum) {
	string string;
	char temp;
	string.resize(stringNum.size());
	for (int i = 0; i < stringNum.size(); i++) {
		temp = (char)(stringNum[i] + 97);
		string += temp;
	}
	cout << string << " " << endl;
	return string;
}

int main() {
	string message,
}