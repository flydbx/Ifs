// AUTHOR : Your Name <your_email@brown.edu>
//
// Ifs.cpp
//

#include "Ifs.h"
#include <iostream>

// VRML'97
//
// IndexedFaceSet {
//   eventIn       MFInt32 set_colorIndex
//   eventIn       MFInt32 set_coordIndex
//   eventIn       MFInt32 set_normalIndex
//   eventIn       MFInt32 set_texCoordIndex
//   exposedField  SFNode  color             NULL
//   exposedField  SFNode  coord             NULL
//   exposedField  SFNode  normal            NULL
//   exposedField  SFNode  texCoord          NULL
//   field         SFBool  ccw               TRUE
//   field         MFInt32 colorIndex        []        # [-1,)
//   field         SFBool  colorPerVertex    TRUE
//   field         SFBool  convex            TRUE
//   field         MFInt32 coordIndex        []        # [-1,)
//   field         SFFloat creaseAngle       0         # [ 0,)
//   field         MFInt32 normalIndex       []        # [-1,)
//   field         SFBool  normalPerVertex   TRUE
//   field         SFBool  solid             TRUE
//   field         MFInt32 texCoordIndex     []        # [-1,)
// }

Ifs::Ifs() {
/* remember to properly initialize all the class variables which do
   not have a default constructor */
}

Ifs::~Ifs(){

};

void           Ifs::clear() {
    _coord.clear();
    _coordIndex.clear();
    _color.clear();
    _normal.clear();
    _normalIndex.clear();
    _texCoord.clear();
    _texCoordIndex.clear();
}
bool&          Ifs::getCcw() { return _ccw; }
bool&          Ifs::getConvex() { return _convex; }
float&         Ifs::getCreaseangle() { return _creaseAngle; }
bool&          Ifs::getSolid() { return _solid; }
bool&          Ifs::getNormalPerVertex() { return _normalPerVertex; }
bool&          Ifs::getColorPerVertex() { return _colorPerVertex; }
vector<float>& Ifs::getCoord() { return _coord;}
vector<int>&   Ifs::getCoordIndex() { return _coordIndex; }
vector<float>& Ifs::getNormal() { return _normal; }
vector<int>&   Ifs::getNormalIndex() { return _normalIndex; }
vector<float>& Ifs::getColor() { return _color; }
vector<int>&   Ifs::getColorIndex() { return _colorIndex; }
vector<float>& Ifs::getTexCoord() { return _texCoord; }
vector<int>&   Ifs::getTexCoordIndex() { return _texCoordIndex; }
void           Ifs::setNormalPerVertex(bool value) { _normalPerVertex=value; }
void           Ifs::setColorPerVertex(bool value) { _colorPerVertex=value; }

// int Ifs::getNumberOfFaces(){}
// int            Ifs::getNumberOfCorners(){}
// int            Ifs::getNumberOfCoord(){}
// int            Ifs::getNumberOfNormal(){}
// int            Ifs::getNumberOfColor(){}
// int            Ifs::getNumberOfTexCoord(){}


// TODO  
Ifs::Binding Ifs::getNormalBinding() {
  if(_normal.size()==0)
    return PB_NONE;
  else if(_normalPerVertex==false)
    if(_normalIndex.size()>0)
      return PB_PER_FACE_INDEXED;
      //assert(_normalIndex.size()==getNumberOfFaces())
    else
      return PB_PER_FACE;
      //assert(normal.size()/3==getNumberOfFaces())
  else  //if(_normalPerVertex==true)
    if(_normalIndex.size()>0)
      return PB_PER_CORNER;
      //assert(normalIndex.size()==coordIndex.size())
    else
      return PB_PER_VERTEX;
      // assert(normal.size()/3==coord.size()/3)
   //return PB_NONE;
}

// TODO  
Ifs::Binding Ifs::getColorBinding() {
   if(_color.size()==0)
  //   NO_COLORS
    return PB_NONE;
  else if(_colorPerVertex==false)
    if(_colorIndex.size()>0)
      return PB_PER_FACE_INDEXED;
      //assert(colorIndex.size()==getNumberOfFaces())
    else
      return PB_PER_FACE;
      // assert(color.size()/3==getNumberOfFaces())
  else //if(colorPerVertex==TRUE)
    if(_colorIndex.size()>0)
      return PB_PER_CORNER;
      // assert(colorIndex.size()==coordIndex.size())
    else
      return PB_PER_VERTEX;
      // assert(color.size()/3==coord.size()/3)
  // return PB_NONE;
}

// TODO  
Ifs::Binding Ifs::getTexCoordBinding() {
  if(_texCoord.size()==0)
    // NO_TEX_COORD
    return PB_NONE;
  else if(_texCoordIndex.size()>0)
    return PB_PER_CORNER;
    // assert(texCoordIndex.size()==coordIndex.size())
  else
    return PB_PER_VERTEX;
    // assert(texCoord.size()/3==coord.size()/3)
  // return PB_NONE;
}

