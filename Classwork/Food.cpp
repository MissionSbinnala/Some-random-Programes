#include<iostream>
using namespace std;

class Food {
private:
	string name;
	float price;
public:
	Food(string n, float p) {
		name = n;
		price = p;
	}
	void PrintFood() {
		cout << name << "\t" << price <<"元"<< endl;
	}
};

int main() {
	Food food[3] = { Food("面包", 5),Food("饮料", 2),Food("饼干", 3.5) };
	food[0].PrintFood();
	food[1].PrintFood();
	food[2].PrintFood();
	return 0;
}