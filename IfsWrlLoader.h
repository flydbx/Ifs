//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2015-10-28 13:12:18 taubin>
//------------------------------------------------------------------------
//
// IfsWrlLoader.h
//
// Software developed for the Fall 2015 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2015, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _IFS_WRL_LOADER_H_
#define _IFS_WRL_LOADER_H_
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "Ifs.h"
#include "IfsLoader.h"
#include "tokenizer.h"


bool my_stof(string str, float & num);

bool my_stoi(string str, int & num);

bool checki(int num, const char * str);

class IfsWrlLoader : public Loader {

private:

const static char* _ext;

public:

  IfsWrlLoader()  {}
  ~IfsWrlLoader() {}

  //This load function is inherited from the base class loader class and
  //we need to first implement it here.

  bool  load(const char* filename, Ifs& ifs);
  const char* ext() const { return _ext; }
 private:
  int _load_point(Tokenizer & tokenizer, vector<float> * vector);
  int _load_index(Tokenizer & tokenizer, vector<int> * vector);
  int _load_bool(Tokenizer & tokenizer, bool * boolVar);

};

#endif /* _IFS_WRL_LOADER_H_ */
