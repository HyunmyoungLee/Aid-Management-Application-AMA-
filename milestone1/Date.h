//Hyunmyoung,Lee
//137925160
//hlee191@myseneca.ca
#ifndef SICT_Date_H_
#define SICT_Date_H_
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace sict{

	
	const int min_year = 2000;
	const int max_year = 2030;
	
	class Date{
		private:
			int year;
			int month;
			int day;
			int compare() const;
			int Error;
			int mdays(int, int) const;
			void errCode(int errorCode);
		public:
			Date();
			Date(int Year,int Month,int Day);
			bool operator==(const Date& rhs) const;
			bool operator!=(const Date& rhs) const;
			bool operator<(const Date& rhs) const;
			bool operator>(const Date& rhs) const;
			bool operator<=(const Date& rhs) const;
			bool operator>=(const Date& rhs) const;
			int errCode() const;
			bool bad() const;
			std::istream& read(std::istream& istr);
			std::ostream& write(std::ostream& ostr) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs);
	std::istream& operator>>(std::istream& istr, Date& rhs);
}
				

#endif	
