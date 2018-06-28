//Hyunmyoung,Lee
//137925160
//hlee191@myseneca.ca
#include "ErrorMessage.h"
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
namespace sict{
	ErrorMessage::ErrorMessage(){
		Message = nullptr;
	}

	ErrorMessage::ErrorMessage(const char* errorMessage){
		Message = nullptr;
		message(errorMessage);
	}

	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		clear();
		message(errorMessage);
		return *this;
	}

	ErrorMessage::~ErrorMessage(){
		delete[] Message;
		Message = nullptr;
	}

	void ErrorMessage::clear(){
		delete[] Message;
		Message = nullptr;
	}

	bool ErrorMessage::isClear() const{
		if(Message == nullptr)
			return true;
		else
			return false;
	}

	void ErrorMessage::message(const char* value){
		clear();
		Message = new char[strlen(value) +1];
		strncpy(Message,value,strlen(value)+1);
	}
	const char* ErrorMessage::message()const{
		return Message;
	}
	std::ostream& ErrorMessage::write(std::ostream& ostr) const{
		ostr<<Message;
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em){
		if(!em.isClear()){
			em.write(ostr);
		}
		return ostr;
	}
}
