#include <iostream>
using namespace std;

class Date {
public:
	Date(int year = 1, int month = 1, int day = 1) {
		//�ж������Ƿ�Ϸ�
		if (year > 0 && month > 0 && month < 13 && day >0 && day < GetMonthDay(year, month)) {
			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "���ڲ��Ϸ�: " << year << "-" << month << "-" << day << endl;
			cout << "��������" << endl;
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
		//4��20�� + 20�� -->  5��40�� --> 5��10��
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
		//4��10�� - 20�� --> 4��-10�� --> 3�� 20��
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
	//ǰ��--
	Date& operator--() {
		return *this -= 1;
	}
	//����--
	Date operator--(int) {
		Date ret(*this);
		ret -= 1;
		return ret;
	}
	//ǰ��++
	Date& operator++() {
		return *this += 1;
	}
	//����++
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