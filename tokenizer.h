#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>
using namespace std;

class Tokenizer : public string {

public:

Tokenizer(ifstream& ifstr):_ifstr(ifstr) { }

bool get();

bool expecting(const string& s);

protected:
	ifstream & _ifstr;
};

#endif // TOKENIZER_H

