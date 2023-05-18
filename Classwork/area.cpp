#include<iostream>
using namespace std;

double Area(double radius = 1.0) {
	double area;
	area = 3.141592653 * radius * radius;
	return area;
}

double Area(double length, double width) {
	double area;
	area = length * width;
	return area;
}

int main() {
	double a, b, area = 0;
	int c;
	cout << "请选择图形(1为圆形，2为方形):\n";
	cin >> c;
	switch (c) {
	case 1:
		cout << "请输入半径：\n";
		cin >> a;
		area = Area(a);
		break;
	case 2:
		cout << "请输入长和宽：\n";
		cin >> a >> b;
		area = Area(a, b);
		break;
	}
	cout << "面积是" << area;
	return 0;
}