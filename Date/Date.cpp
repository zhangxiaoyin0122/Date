#include <iostream>
using namespace std;

class Date {
public:
	Date(int year = 1, int month = 1, int day = 1) {
		//判断日期是否合法
		if (year > 0 && month > 0 && month < 13 && day >0 && day < GetMonthDay(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "日期不合法: " << year << "-" << month << "-" << day << endl;
			cout << "日期重置" << endl;
			_year = 1;
			_month = 1;
			_day = 1;
		}
	}
	int GetMonthDay(int year, int month) {
		int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[month];
		if ((month==2)&&((year % 4 == 0 )&& (year % 100 == 0)) || (year % 400 == 0)) {
			day++;
		}
		return day;
	}

	Date& operator+=(int day) {
		if (day < 0) {
			return *this -= -day;
		}
		_day += day;
		//4月20日 + 20日 -->  5月40日 --> 5月10号
		while (_day  > GetMonthDay(_year,_month)) {
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13) {
				_month = 1;
				_year++; 
			}
		}
		return *this;
	}
	Date& operator-=(int day) {
		if (day < 0) {
			return *this += -day;
		}
		_day -= day;
		//4月10号 - 20天 --> 4月-10号 --> 3月 20号
		while (_day <= 0) {
			_month--;
			if (_month == 0) {
				_month = 12;
				_year--;
			}
			_day += GetMonthDay(_year, _month);			
		}
		return *this;
	}
	Date& operator-=(int day);
	//前置--
	Date& operator--() {
		return *this -= 1;
	}
	//后置--
	Date operator--(int) {
		Date ret(*this);
		ret -= 1;
		return ret;
	}
	//前置++
	Date& operator++() {
		return *this += 1;
	}
	//后置++
	Date operator++(int) {
		Date ret(*this);
		ret += 1;
		return ret;
	}
	Date operator+(int day) {
		Date ret(*this);
		ret += day;
		return *this;
	}
	Date operator-(int day) {
		Date ret(*this);
		ret -= day;
		return ret;
	}
	bool operator==(const Date& date) {
		return _year == date._year
			&&_month == date._month
			&&_day == date._day;
	}
	bool operator>(const Date& date) {
		if (_year > date._year) {
			return true;
		}
		else if(_year == date._year){
			if (_month > date._month) {
				return true;
			}
			else if(_month == date._month){
				if (_day > date._day)
					return true;
			}
		}
		return false;
	}
	bool operator>=(const Date& date) {
		return (*this > date) || (*this == date);
	}
	bool operator<(const Date& date) {
		return !(*this >= date);
	}
	bool operator <=(const Date& date) {
		return !(*this > date);
	}
	
	int operator-(const Date& date) {
		Date  d1(*this);
		Date d2(date);
		int num = 0;
		if (d1 > d2) {
			while (d1 > d2) {
				--d1;
				num++;
			}
			return num;
		}
		else {
			while (d1 < d2) {
				++d1;
				num++;
			}
			return -num;
		}
	}
private:
	int _year;
	int _month;
	int _day;
};