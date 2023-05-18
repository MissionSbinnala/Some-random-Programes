#include<iostream>

using namespace std;

class Time {
private:
	int hour;
	int minute;
	int second;
public:
	Time(int h, int m, int s) {
		hour = h;
		minute = m;
		second = s;
		while (second >= 60|| minute >= 60|| hour >= 24) {
			if (second >= 60)
			{
				second = second - 60;
				minute++;
			}
			if (minute >= 60)
			{
				minute = minute - 60;
				hour++;
			}
			if (hour >= 24) {
				hour = hour - 24;
			}
		}
	}
	Time() {
		hour = 0;
		minute = 0;
		second = 0;
	}
	void show() {
		cout << hour << ":" << minute << ":" << second << endl;
	}
	Time operator ++ () {
		second++;
		if (second == 60)
		{
			second = 0;
			minute++;
		}
		if (minute == 60)
		{
			minute = 0;
			hour++;
		}
		if (hour == 24) {
			hour = 0;
		}
		return *this;
	}
	friend Time operator - (Time t1, Time t2) {
		t1.hour = t1.hour - t2.hour;
		t1.minute = t1.minute - t2.minute;
		t1.second = t1.second - t2.second;
		while (t1.second <= 0 || t1.minute <= 0 || t1.hour <= 0) {
			if (t1.second <= 0)
			{
				t1.second = t1.second + 60;
				t1.minute--;
			}
			if (t1.minute <= 0)
			{
				t1.minute = t1.minute + 60;
				t1.hour--;
			}
			if (t1.hour <= 0) {
				t1.hour = t1.hour + 24;
			}
		}
		return t1;
	}
};

int main() {
	Time t1(10, 59, 10), t2(15, 5, 5);
	t1.show();
	++t1;
	t1.show();
	t1 = t1 - t2;
	t1.show();
	return 0;
}