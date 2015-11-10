#include <fstream>
#include <iostream>
#include <string>
#include "tokenizer.h"

using namespace std;

bool Tokenizer::get()
{
	

	char temp=_ifstr.get();

	this->clear();
	
	while((isspace(temp) || temp==',') && !_ifstr.eof())	{
		temp=_ifstr.get();
	}

	if(_ifstr.eof()){
		return false;
	}

	while(temp!=',' && !isspace(temp) && !_ifstr.eof())
	{
		* this+=temp;
		char check=_ifstr.peek();
		if(check=='{' || check=='}' || check=='[' || check==']'){
			cerr<<"Syntax error"<<endl;
			return false;
		}
		temp=_ifstr.get();
		
	}



	return true;
}


bool Tokenizer::expecting(const string& str){
	return get() && (str == *this);
}
