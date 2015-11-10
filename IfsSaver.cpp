// AUTHOR : Your Name <your_email@brown.edu>
//
// IfsSaver
//

#include "IfsSaver.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool IfsSaver::save(const char* filename, Ifs& ifs) {
  bool success = false;
  string filename_str=string(filename);

  if(filename!=(const char*)0) {
    // ofstream is(filename);
    // if(!is){ 
    //   cerr<<"Fail to open the output file."<<endl;
    //   return success;
    // }

    unsigned i = filename_str.find('.');
    if(i==filename_str.npos) return 0;

    string ext=filename_str.substr(i+1,3);

    Saver * saver=_registry[ext];
    if(!saver) {
      cerr<<"Fail to find the saver!"<<endl;
      return 0;
    }
    success=saver->save(filename, ifs);
  }
  return success;
}

void IfsSaver::registerSaver(Saver* saver) {
  if(saver!=(Saver*)0) {
  	string ext=saver->ext();
  	pair<string, Saver *> p(ext, saver);
  	_registry.insert(p);
  }
}
