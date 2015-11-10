//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2015-10-28 13:09:35 taubin>
//------------------------------------------------------------------------
//
// IfsLoader.h
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

#ifndef _IfsLoader_h_
#define _IfsLoader_h_

#include <map>
#include <string>
#include "Ifs.h"

class Loader {
    //This is the basis for each loader whatever type of files the loader is for

public:
    //This is a pure virtual function
    //each file type has to implement its own version.
  virtual bool  load(const char* filename, Ifs& ifs) = 0;
  virtual const char* ext() const = 0;

};

class IfsLoader {
    //This is the factory. The loaders for each type of files must be
    //registered here.

public:

  IfsLoader() {}
  ~IfsLoader() {}

  bool load(const char* filename, Ifs& ifs);
  void registerLoader(Loader* loader);

private:

  map<string, Loader*> _registry;

};

#endif /* _IfsLoader_ */
