//Hyunmyoung,Lee
//137925160
//hlee191@myseneca.ca
#define _CRT_SECURE_NO_WARNINGS
#include "NonPerishable.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

namespace sict{
	void NonPerishable::name(const char* Name){
		_name = new char[max_name_length];
		strcpy(_name,Name);
		if(Name == nullptr){
			delete []_name;
		}
	}
	const char* NonPerishable::name() const{
		if(_name == nullptr){
			return nullptr;
		}else{
			return _name;
		}
	}
	double NonPerishable::cost() const{
		if(check){
			return price*(1 + Tax) ;
		}else{
			return price;
		}
	}
	void NonPerishable::message(const char* Error){
		error.message(Error);
	}
	bool NonPerishable::isClear() const{
		if(error.isClear())
			return true;
		else
			return false;
	}
	NonPerishable::NonPerishable(){
		type = 'N';
		sku[0] = '\0';
		_name = nullptr;
		unit[0] = '\0';
		CurrentQTY = 0;
		NeededQTY = 0;
		price = 0;
		check = true;
	}
	NonPerishable::NonPerishable(char Type){
		type = Type;
		NonPerishable();
	}
	NonPerishable::NonPerishable(const char* Sku, const char* Name, const char* Unit, int cQTY, bool Check, double Price, int nQTY){
		_name = new char[max_name_length+1];
		strcpy(sku,Sku);
		strcpy(_name,Name);
		strcpy(unit,Unit);
		CurrentQTY = cQTY;
		NeededQTY = nQTY;
		check = Check;
		price = Price;
	}
	NonPerishable::NonPerishable(const NonPerishable& np){
	_name = new char[max_name_length+1];
	strcpy(sku,np.sku); 
	strcpy(_name, np._name);
	strcpy(unit, np.unit);
	CurrentQTY = np.CurrentQTY;
	NeededQTY = np.NeededQTY;
	check = np.check;
	price = np.price;
	}
	NonPerishable& NonPerishable::operator=(const NonPerishable& np){
		if(this != &np){
		delete[] _name;
		strcpy(sku,np.sku);
		strcpy(unit, np.unit);
		CurrentQTY = np.CurrentQTY;
		NeededQTY = np.NeededQTY;
		check = np.check;
		price = np.price;
		if(np._name == nullptr){
			_name = nullptr;
		}else{
			_name = new char[max_name_length];
			strcpy(_name, np._name);
		}
		}

		return *this;
	}
	NonPerishable::~NonPerishable(){
		delete []_name;
		_name = nullptr;
	}
	std::fstream& NonPerishable::store(std::fstream& file, bool newLine) const{
		if(file.is_open()){
			file << type << ','
			     << sku << ','
			     << _name << ',' 
			     << price<< ','
			     << check<< ',' 
			     << CurrentQTY << ','
			     << unit<< ','
			     << NeededQTY;
		
		if(newLine){
			file << endl;
		}
		}
		return file;
	}
	std::fstream& NonPerishable::load(std::fstream& file){
		char Sku[max_sku_length+1];
		char Name[max_name_length+1];
		double Price;
		bool Check;
		int current;
		int needed;
		char Unit[max_unit_length+1];
		char a = ',';
			if(file.is_open()){
			file.getline(Sku,max_sku_length+1, a);
			file.getline(Name,max_name_length+1,a);
			file >> Price;
			file.ignore(10,',');
			file >> Check;
			file.ignore(10,',');
			file >> current;
			file.ignore(10,',');
			file.getline(Unit, max_unit_length+1, a);
			file >> needed;
			file.ignore(10,',');
			strcpy(sku,Sku);
			name(Name);
			strcpy(unit,Unit);
			check = Check;
			price = Price;
			CurrentQTY = current;
			NeededQTY = needed;
			}
		return file;
			
	}
	std::ostream& NonPerishable::write(std::ostream& os, bool linear) const{
		if(error.isClear()){
		if(linear == true){
			os << std::setw(max_sku_length) << std::left << sku <<"|";
			os << std::setw(20) << std::left << _name << "|";
			os << std::setw(7) << std::fixed << std::right << std::setprecision(2) << NonPerishable::cost() << "|";
			os << std::setw(4) << std::right << CurrentQTY << "|";
			os << std::setw(10) << std::left << unit << "|";
			os << std::setw(4) << std::right << NeededQTY << "|";
		}else{
			os << "Sku: " << sku << endl;
			os << "Name: " << _name <<endl;
			os << "Price: " << std::fixed << price << endl;
			os << "Price after tax: " ;
		       if(check == true){
		       	       os <<std::fixed <<  NonPerishable::cost() <<endl;
		       }else{
				os << "N/A" << endl;
		       }
			os << "Quantity On Hand: " << CurrentQTY << " " << unit << endl;
			os << "Quantity Needed: " << NeededQTY;
		}
		}else{
		os << error.message();
	}
		return os;
	
	}
	std::istream& NonPerishable::read(std::istream& is){
		char Sku[max_sku_length];
		char Name[max_name_length];
		char Unit[max_unit_length];
		char Ch;
		double Price;
		int current;
		int needed;

		error.clear();
		cout<< " Sku: ";
		is.getline(Sku,max_sku_length, '\n');
		if(is.fail()){
			return is;
		}
		strcpy(sku, Sku);
		cout << " Name: ";
		is.getline(Name,max_name_length,'\n');
		if(is.fail()){
			return is;
		}
		name(Name);
		cout << " Unit: ";
		is.getline(Unit,max_unit_length,'\n');
		if(is.fail()){
			return is;
		}
		strcpy(unit, Unit);
		if (error.isClear()){
			cout << " Taxed? (y/n): ";
			is >> Ch;
			if (is.fail()){
				error.message("Only (Y)es or (N)o are acceptable");
				is.setstate(ios::failbit);
			}else{
				if(Ch == 'Y' || Ch == 'y'){
					check = true;
				}
				else if( Ch == 'N' || Ch == 'n'){
					check = false;
				}else{
					error.message("Only (Y)es or (N)o are acceptable");
					is.setstate(ios::failbit);
				}
			}
		}else{
			return is;
		}
		if(error.isClear()){
			cout<<" Price: ";
			is >> Price;
			if(is.fail()){
				error.message("Invalid Price Entry");
				is.setstate(ios::failbit);
			}else{
				price = Price;
			}
		} else{
			return is;
		}

		if(error.isClear()){
			cout << "Quantity On hand: ";
			is >> current;
			if(is.fail()){
				error.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
			}else{
				CurrentQTY = current;
			}
		}else{
			return is;
		}
		if(error.isClear()){
			cout<< "Quantity Needed: ";
			is>> needed;
			if(is.fail()){
				error.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
			}else{
				NeededQTY = needed;
			}
		
		}
		return is;
	}
	bool NonPerishable::operator==(const char* Sku) const{
		if(strcmp(Sku,sku) == 0){
			return true;
		}else{
			return false;
		}
	}
	double NonPerishable::total_cost() const{
		return CurrentQTY * NonPerishable::cost();
	}
	void NonPerishable::quantity(int num){
		CurrentQTY = num;
	}
	bool NonPerishable::isEmpty() const{
		if(sku[0] == '\0' && _name == nullptr && price == 0 && CurrentQTY == 0 && check == true){
			return true;
		}else{
			return false;
		}
	}
	int NonPerishable::qtyNeeded() const{
		return NeededQTY;
	}
	int NonPerishable::quantity() const{
		return CurrentQTY;
	}
	bool NonPerishable::operator>(const char* Sku) const{
		int a = strlen(Sku);
		int b = strlen(sku);
		if( a > b){
			return true;
		}else{
			return false;
		}
	}
	int NonPerishable::operator+=(int num){
		if(num > 0){
			return CurrentQTY+=num;
		}else{
			return CurrentQTY;
		}
	}
	bool NonPerishable::operator>(const Product& pr) const{
		int a = strlen(_name);
		int b = strlen(pr.name());
		if( a > b){
			return true;
		}else{
			return false;
		}
	}
	std::ostream& operator<<(std::ostream& os, const Product& pr){
		pr.write(os,true);
		return os;
	}
	std::istream& operator>>(std::istream& is, Product& pr){
		pr.read(is);
		return is;
	}
	double operator+=(double& db, const Product& pr){
		db += pr.total_cost();
		return db;
	}
	Product* CreateProduct(){
		Product* np;
		np = new NonPerishable;
		return np;
	}
}

