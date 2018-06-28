//Hyunmyoung, Lee
//137925160
//hlee191@myseneca.ca
#ifndef SICT_NONPERISHABLE_H_
#define SICT_NONPERISHABLE_H_
#include "Product.h"
#include "ErrorMessage.h"
namespace sict{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double Tax = 0.13;

	class NonPerishable : public Product{
		private:
			char type;
			char sku[max_sku_length];
			char* _name;
			char unit[max_unit_length];
			int CurrentQTY;
			int NeededQTY;
			double price;
			bool check;
	
		protected:
			ErrorMessage error;
			void name(const char*);
			const char* name() const;
			double cost() const;
			void message(const char*);
			bool isClear() const;
		public:
			NonPerishable();
			NonPerishable(char Type);
			NonPerishable(const char* Sku, const char* Name, const char* Unit,int cQTY=0, bool Check=true, double Price=0, int nQTY=0);
		       	NonPerishable(const NonPerishable&);
			NonPerishable& operator=(const NonPerishable&);
			~NonPerishable();
			std::fstream& store(std::fstream& file, bool newLine=true) const;
			std::fstream& load(std::fstream& file);
			std::ostream& write(std::ostream& os, bool linear) const;
			std::istream& read(std::istream& is);
			bool operator==(const char*) const;
			double total_cost() const;
			void quantity(int);
			bool isEmpty() const;
			int qtyNeeded() const;
			int quantity() const;
			bool operator>(const char*) const;
			int operator+=(int);
			bool operator>(const Product&) const;
	};
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator+=(double&, const Product&);
	Product* CreateProduct();
}
#endif		
