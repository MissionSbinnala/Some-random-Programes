#include<iostream>
#include<string>
using namespace std;

class Book {
protected:
	string title;
	float price;
public:
	Book(string t, float p) {
		title = t;
		price = p;
	}
	void show() {
		cout << "Title:" << title << endl;
		cout << "Price:" << price << endl;
	}
};

class ProgBook :public Book {
protected:
	string proglang;
public:
	ProgBook(string t, float p, string pl) :Book(t,p){
		proglang = pl;
	}
	void show() {
		Book::show();
		cout << "Proglang:" << proglang << endl;
	}
};

int main() {
	ProgBook pb("面向对象程序设计",45.0, "C++");
	pb.show();
	return 0;
}