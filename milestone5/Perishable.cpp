//Hyunmyoung,Lee
//137925160
//hlee191@myseneca.ca
#include "Perishable.h"
#include "Date.h"
#include "NonPerishable.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

namespace sict{
	Perishable::Perishable() : NonPerishable('P'){

	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const{
		NonPerishable::store(file, false); // Shadowing
		file << "," << ExpireDate; //append expiry date
		if(newLine == true){
			file << endl;
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file){
		NonPerishable::load(file); //Shadowing
		ExpireDate.read(file); //Using read function of Data
		file.ignore(1);
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const{
		NonPerishable::write(os, linear); 
		if(NonPerishable::isClear() && !isEmpty()){
			if(linear == true){
			os << ExpireDate;
			}else{
				os << endl;
				os << "Expiry date: " << ExpireDate;
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is){
		Date tempDate; //Temporary date
		NonPerishable::read(is);
		if(NonPerishable::isClear()){
			cout << "Expiry date (YYYY/MM/DD): ";
			is >> tempDate; // Store Temporary date
			if(tempDate.errCode() == CIN_FAILED){
				NonPerishable::message("Invalid Date Entry");//Store appropriate error message
				is.setstate(std::ios::failbit); // set the state of the istream object to a failed state.
			}else if(tempDate.errCode() == YEAR_ERROR){
				NonPerishable::message("Invalid Year in Date Entry");
				is.setstate(std::ios::failbit);
			}else if(tempDate.errCode() == MON_ERROR){
				NonPerishable::message("Invalid Month in Date Entry");
				is.setstate(std::ios::failbit);
			}else if(tempDate.errCode() == DAY_ERROR){
				NonPerishable::message("Invalid Day in Date Entry");
				is.setstate(std::ios::failbit);
			}else{
				ExpireDate = tempDate;
		}
		}
		return is;
	}
	const Date& Perishable::expiry() const{
		return ExpireDate;
	}
	Product* CreatePerishable(){
		Product* pr;
		pr = new Perishable;
		return pr;
	}
}

