//Hyunmyoung, Lee
//137925160
//hlee191@myseneca.ca
#include <iostream>
#include <iomanip>
#include "Date.h"
using namespace std;
namespace sict{
	Date::Date(){
		year = 0;
		month = 0;
		day = 0;
		Error = NO_ERROR;
	}

	Date::Date( int Year,  int Month,  int Day){
		if(Year>=min_year && Year<=max_year && Month >=1 && Month <=12 && Day>=1 && Day<=mdays(Month,Year)){
			year = Year;
			month = Month;
			day = Day;
			Error = NO_ERROR;
		}else{
			*this = Date();
		}
	}
	int Date::mdays(int mon, int year) const{
		int days[] = {31,28,31,30,31,30,31,31,30,31,30,31,-1};
		int month = mon >= 1&& mon <= 12 ? mon : 13;
		month --;
		return days[month]+int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode){
		Error = errorCode;
	}
	int Date::compare() const{
		return year*372+month*13+day;
	}
	bool Date::operator==(const Date& rhs) const{
		return this->compare() == rhs.compare();
	}
	bool Date::operator!=(const Date& rhs) const{
		return this->compare() != rhs.compare();
	}
	bool Date::operator<(const Date& rhs) const{
		return this->compare() < rhs.compare();
	}
	bool Date::operator>(const Date& rhs) const{
		return this->compare() > rhs.compare();
	}
	bool Date::operator<=(const Date& rhs) const{
		return this->compare() <= rhs.compare();
	}
	bool Date::operator>=(const Date& rhs) const{
		return this->compare() >= rhs.compare();
	}
	int Date::errCode() const{
		return Error;
	}
	bool Date::bad() const{
		if(Error != NO_ERROR)
			return true;
		else
			return false;
	}
	std::istream& Date::read(std::istream& istr){
		char a,b;
		Error = NO_ERROR;
		istr >> year >> a >> month >> b >> day ;
		if(istr.fail()){
			Error = CIN_FAILED;
		}else if(year > max_year || year < min_year){
			Error = YEAR_ERROR;
		}else if(month > 12 || month < 1){
			Error = MON_ERROR;
		}else if(day < 1 && day > mdays(month,year)){
		       Error = DAY_ERROR;
		}	       

		return istr;

	}
	std::ostream& Date::write(std::ostream& ostr) const{
		ostr.setf(std::ios::fixed);
		ostr.setf(std::ios::right);
		ostr << year << "/";
		ostr.setf(std::ios::right);
		ostr.width(2);
		ostr.fill('0');
		ostr << month << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << day;
		ostr.fill(' ');
		ostr.unsetf(std::ios::fixed);
		return ostr;
	}
	
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs){
		return rhs.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Date& rhs){
		return rhs.read(istr);
	}
}


