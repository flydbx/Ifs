// AUTHOR : Your Name <your_email@brown.edu>
//
// IfsLoader
//

#include "IfsLoader.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool IfsLoader::load(const char* filename, Ifs& ifs) {
  bool success = false;
  string filename_str=string(filename);
  if(filename!=(const char*)0) {
    // ifstream is(filename);
    // if(!is) return 0;

    unsigned i = filename_str.find('.');
    if(i==filename_str.npos) return 0;

    string ext=filename_str.substr(i+1,3);

    Loader * ld=_registry[ext];
    if(!ld) return 0;
    success=ld->load(filename, ifs);
  }
  return success;
}

void IfsLoader::registerLoader(Loader* loader) {
  if(loader!=(Loader*)0) {
    string ext=loader->ext();
    pair<string, Loader *> p(ext, loader);
    _registry.insert(p);
  }
}
