#include<iostream>

using namespace std;

class Human {
public:
	virtual void SayHello() = 0;
	virtual ~Human() {};
};

class Chinese :public Human {
public:
	Chinese() {};
	void SayHello() {
		cout << "ÄãºÃ£¡" << endl;
	}
};

class Brithish :public Human {
public:
	Brithish() {};
	void SayHello() {
		cout << "Hello!" << endl;
	}
};

class French :public Human {
public:
	French() {};
	void SayHello() {
		cout << "Bonjour!" << endl;
	}
};

void Hello(Human *human) {
	human->SayHello();
}

int main() {
	Chinese c;
	Brithish b;
	French f;
	Hello(&c);
	Hello(&b);
	Hello(&f);
	return 0;
}