#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Rotor {
public:
	Rotor(vector<int> l, vector<int> r) {
		left = l;
		right = r;
		next = nullptr;
		current = 0;
	}
	Rotor(vector<int> l, vector<int> r, Rotor* n) {
		left = l;
		right = r;
		next = n;
		current = 0;
	}
	void Rotate() {
		current++;
		current = current % 26;
		if (current == 0) {
			next->Rotate();
		}
	}
	int Match(int x) {
		if (x < 0 || x > 25) {
			return -1;
		}
		x = (x + current) % 26;
		for (int i = 0; i < 26; i++) {
			if (right[i] == left[x]) {
				int temp = i - current;
				if (temp < 0) {
					temp += 26;
				}
				return temp;
			}
		}
		return -1;
	}
	int Rematch(int x) {
		if (x < 0 || x > 25) {
			return -1;
		}
		x = (x + current) % 26;
		for (int i = 0; i < 26; i++) {
			if (left[i] == right[x]) {
				int temp = i - current;
				if (temp < 0) {
					temp += 26;
				}
				return temp;
			}
		}
		return -1;
	}
private:
	vector<int> left, right;
	int current = 0;
	Rotor* next;
};

int main() {
	vector<int> firstL = { 23,24,25,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 },
		firstR = { 20,2,14,0,18,9,13,25,19,7,15,6,21,3,10,4,16,8,11,22,17,1,24,5,23,12 },
		secondL = { 25,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 },
		secondR = { 19,0,5,3,14,2,13,11,22,4,15,1,21,18,10,17,24,23,12,6,9,7,20,8,25,16 },
		thirdL = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 },
		thirdR = { 7,17,25,16,19,21,9,2,12,10,3,22,4,23,8,11,24,15,18,5,14,20,1,6,0,13 };
	Rotor third(thirdL, thirdR), second(secondL, secondR, &third), first(firstL, firstR, &second);
	string message, cry;
	cout << "请输入文本:";
	cin >> message;
	cry.resize(message.size());
	for (int i = 0; i < message.size(); i++) {
		int temp = message[i] - 97;
		if (temp < 0) {
			temp += 32;
		}
		cry[i] = first.Rematch(second.Rematch(third.Rematch(25 - third.Match(second.Match(first.Match(temp)))))) + 97;
		if (cry[i] == 96) {
			cout << "输入错误";
			return 0;
		}
		first.Rotate();
	}
	cout << "结果为:" << cry;
}
//abcdefghijklmnopqrstuvwxyz
