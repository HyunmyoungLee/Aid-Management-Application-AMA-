//Hyunmyoung, Lee
//137925160
//hlee191@myseneca.ca
#ifndef SICT_PERISHABLE_H_
#define SICT_PERISHABLE_H_
#include "NonPerishable.h"
#include "Date.h"
namespace sict{
	class Perishable : public NonPerishable{
		private:
			Date ExpireDate;
		public:
			Perishable();
			std::fstream& store(std::fstream& file, bool newLine=true) const;
			std::fstream& load(std::fstream& file);
			std::ostream& write(std::ostream& os, bool linear) const;
			std::istream& read(std::istream& is);
		 	const Date& expiry() const;
	};
	Product* CreatePerishable();
}

#endif
