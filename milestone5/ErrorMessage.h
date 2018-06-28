//Hyunmyoung,Lee
//137925160
//hlee191@myseneca.ca

#ifndef Sict_ErrorMessage_H_
#define Sict_ErrorMessage_H_
#include <iostream>
namespace sict{
	class ErrorMessage{
		private:
			char* Message;
		public:
			ErrorMessage();
			ErrorMessage(const char* errorMessage);
			ErrorMessage(const ErrorMessage& em) = delete;
			ErrorMessage& operator=(const ErrorMessage& em) = delete;
			ErrorMessage& operator=(const char* errorMessage);
			virtual ~ErrorMessage();
			void clear();
			bool isClear() const;
			void message(const char* value);
			const char* message() const;
			std::ostream& write(std::ostream& ostr)const;
	};
	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em);
}
#endif
