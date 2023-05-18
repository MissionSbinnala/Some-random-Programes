#include<iostream>
using namespace std;

class Person {
protected:
	int id;
	string name;
public:
	Person(int i, string n) {
		id = i;
		name = n;
	}
	void Display() {
		cout << "ID:" << id << endl;
		cout << "Name:" << name << endl;
	}
};

class Student :public Person {
protected:
	int score;
	string dept;
public:
	Student(int i, string n, string d, int s) :Person(i,n){
		score = s;
		dept = d;
	}
	void Display() {
		Person::Display();
		cout << "Dept:" << dept << endl;
		cout << "Score=" << score << endl;
	}
};

int main() {
	Student stu1(1, "Wang", "Network", 99);
	stu1.Display();
	return 0;
}