#ifndef CLASS_H
#define CLASS_H

#ifndef STRING
#define STRING
#include<string>
#endif // !STRING

class Clock;

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
	}
	Time() {
		hour = 0;
		minute = 0;
		second = 0;
	}
	bool SecondI() {
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
			return true;
		}
		else {
			return false;
		}
	}
	bool SecondD() {
		second--;
		if (second <= 0) {
			minute--;
			second = second + 60;
		}
		if (minute <= 0) {
			hour--;
			minute = minute + 60;
		}
		if (hour == -1) {
			return true;
		}
		else {
			return false;
		}
	}
	void HourI() {
		hour = hour - 24;
		return;
	}
	void HourD() {
		hour = hour + 24;
		return;
	}
	int RH() {
		return hour;
	}
	int RM() {
		return minute;
	}
	int RS() {
		return second;
	}
};

class Date {
private:
	int year, month, day, limit;
public:
	Date(int y, int m, int d, int l = 30) {
		year = y;
		month = m;
		day = d;
		limit = l;
	}
	Date() {
		year = 0;
		month = 0;
		day = 0;
		limit = 30;
	}
	int MonthCheck() {
		int isLeapYear = 0;
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			isLeapYear = 1;
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			limit = 31;
		}
		if (month == 2) {
			if (isLeapYear == 1) {
				limit = 29;
			}
			else {
				limit = 28;
			}
		}
		return limit;
	}
	void DayI() {
		day++;
		if (day > limit) {
			day = day - limit;
			month++;
			limit = MonthCheck();
		}
		if (month > 12) {
			year++;
			month = month - 12;
			limit = MonthCheck();
		}
		return;
	}
	void DayD() {
		day--;
		if (day == 0) {
			day = day + limit;
			month--;
			limit = MonthCheck();
		}
		if (month == 0) {
			month = month + 12;
			limit = MonthCheck();
		}
		return;
	}
	int RY() {
		return year;
	}
	int RM() {
		return month;
	}
	int RD() {
		return day;
	}
	void YD() {
		year -= 1;
	}
};

class Clock {
protected:
	std::string brand;
	double price;
	Time time;
	Date date;
public:
	Clock(std::string b, double p, Time t, Date d) {
		brand = b;
		price = p;
		time = t;
		date = d;
		date.MonthCheck();
		if (date.RM() == 1 && date.RD() == 1) {
			date.YD();
		}
		date.DayD();
		date.DayI();
	}
	Clock() {
		brand = "a";
		price = 0;
		time = Time(0, 0, 0);
		date = Date(0, 0, 0);
	}
	void SecondI(int s) {
		int i;
		for (i = 0; i < s; i++) {
			if (time.SecondI()) {
				time.HourI();
				DayI(1);
			}
		}
		return;
	}
	void SecondD(int s) {
		int i;
		for (i = 0; i < s; i++) {
			if (time.SecondD()) {
				time.HourD();
				DayD(1);
			}
		}
		return;
	}
	void DayI(int d) {
		int i;
		for (i = 0; i < d; i++) {
			date.DayI();
		}
		return;
	}
	void DayD(int d) {
		int i;
		for (i = 0; i < d; i++) {
			date.DayD();
		}
		return;
	}
	int RH() {
		return time.RH();
	}
	int RM() {
		return time.RM();
	}
	int RS() {
		return time.RS();
	}
	int RY() {
		return date.RY();
	}
	int RMon() {
		return date.RM();
	}
	int RD() {
		return date.RD();
	}
	int RP() {
		return price;
	}
	std::string RB() {
		return brand;
	}
};

class MechClock :virtual public Clock {
protected:
	int spring;
public:
	MechClock(std::string b, double p, Time t, Date d, int s) :Clock(b, p, t, d) {
		spring = s;
	}
	MechClock() {}
	MechClock(int s) {
		spring = s;
	}
	int RSP() {
		return spring;
	}
	void SpringD() {
		spring--;
	}
};

class ElecClock :virtual public Clock {
protected:
	int battery;
public:
	ElecClock(std::string b, double p, Time t, Date d, int ba) :Clock(b, p, t, d) {
		battery = ba;
	}
	ElecClock() {}
	ElecClock(int ba) {
		battery = ba;
	}
	int RBA() {
		return battery;
	}
	void BatteryD() {
		battery--;
	}
};

class MEClock :public MechClock, public ElecClock {
public:
	MEClock(std::string b, double p, Time t, Date d, int s, int ba) :Clock(b, p, t, d), MechClock(s), ElecClock(ba) {}
	MEClock() {
		brand = "a";
		price = 0;
		time = Time(0, 0, 20);
		date = Date(0, 3, 5);
		spring = 0;
		battery = 0;
	}
	void Move(MEClock me1) {
		brand = me1.brand;
		price = me1.price;
		time = me1.time;
		date = me1.date;
		spring = me1.spring;
		battery = me1.battery;
	}
};

#endif // CLASS_H
