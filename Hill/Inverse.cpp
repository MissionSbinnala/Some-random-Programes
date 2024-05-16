#include <iostream>
#include <numeric>
#include <vector>
#include <stdlib.h>
#include<string>

using namespace std;

int seed = time(0);

vector<vector<double>> Initialize(vector<vector<double>> matrix, int size) {
	vector<double> temp;
	temp.resize(size, 1);
	matrix.resize(size, temp);
	srand(seed);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = rand() % 26;
		}
	}
	seed += 20 % 2 ^ 15;
	return matrix;
}

int Calc(vector<vector<double>> matrix, int size) {
	double detVal = 0;//行列式的值
	if (size == 1)//递归终止条件 
		return matrix[0][0];
	vector<vector<double>> next;
	vector<double> temp;
	temp.resize(size - 1, 0);
	next.resize(size - 1, temp);
	for (int i = 0; i < size; i++)//第一重循环，行列式按第一行展开 
	{
		for (int j = 0; j < size - 1; j++)
			for (int k = 0; k < size - 1; k++)
			{
				if (k < i)
					next[j][k] = matrix[j + 1][k];
				else
					next[j][k] = matrix[j + 1][k + 1];
			}
		detVal += matrix[0][i] * pow(-1.0, i) * Calc(next, size - 1);
	}
	return detVal;
}

vector <vector<double>> Adjoint(vector<vector<double>> matrix, int size) {
	if (size == 1)//递归终止条件 
		return matrix;
	vector<vector<double>> changed, next;
	vector<double> temp;
	temp.resize(size - 1, 0);
	changed.resize(size - 1, temp);
	temp.resize(size, 0);
	next.resize(size, temp);
	for (int i = 0; i < size; i++)//第一重循环，行列式按第一行展开 
	{
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++)
			{
				for (int m = 0; m < size; m++) {
					if (k < i) {
						if (m < j) {
							changed[k][m] = matrix[k][m];
						}
						else if (m > j) {
							changed[k][m - 1] = matrix[k][m];
						}
					}
					else if (k > i) {
						if (m < j) {
							changed[k - 1][m] = matrix[k][m];
						}
						else if (m > j) {
							changed[k - 1][m - 1] = matrix[k][m];
						}
					}
				}
			}
			next[j][i] = pow(-1.0, (i + 1) + (j + 1)) * Calc(changed, size - 1);
		}
	}
	return next;
}

vector<vector<string>> Inverse(vector <vector<double>> adjoint, int size, int determinants) {
	vector<vector<string>> inverse;
	vector<string> temp;
	temp.resize(size," ");
	inverse.resize(size, temp);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			double temp;
			temp = adjoint[i][j] / determinants;
			if (temp - (int)temp != 0) {
				inverse[i][j] =to_string((int)adjoint[i][j]) + '/' + to_string((int)determinants);
				if (inverse[i][j].length() <= 8) {
					inverse[i][j] += "       ";
				}
			}
			else {
				inverse[i][j] = to_string((int)temp);
				if (inverse[i][j].length() <= 8) {
					inverse[i][j] += "       ";
				}
			}
		}
	}
	return inverse;
}

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void Display(vector<vector<double>> matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void Display(vector<vector<string>> matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

int Inverse() {
	int size;
	cin >> size;
	vector<vector<double>> matrix, adjoint;
	vector<vector<string>> inverse;
	vector<double> temp;
	temp.resize(size, 0);
	adjoint.resize(size, temp);
	int determinants = 2;
	do {
		matrix = Initialize(matrix, size);
		determinants = Calc(matrix, size);
	} while (gcd(determinants%26, 26) != 1);
	adjoint = Adjoint(matrix, size);
	Display(matrix, size);
	cout << endl;
	Display(adjoint, size);
	inverse = Inverse(adjoint, size, determinants);
	cout << endl;
	Display(inverse, size);
	cout << endl;
	cout << determinants;
}