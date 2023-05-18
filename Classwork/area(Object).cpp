#include<iostream>
using namespace std;

class Circle {
private:
	double radius;           //°ë¾¶
	double area;
public:
	void set_radius(double r) {
		radius = r;
		return;
	};   //ÉèÖÃÔ²µÄ°ë¾¶
	double get_radius() { 
		return this->radius;
	};           //·µ»ØÔ²µÄ°ë¾¶ 
	};

int main() {
	Circle circle2;
	double r, area;
	cout << "Please input the radius of the circle:"<<endl;
	cin >> r;
	circle2.set_radius(r);
	area = circle2.get_radius() * circle2.get_radius() * 3.14159;
	cout << "Area=" << area << endl;
	return 0;
}