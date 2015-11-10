// AUTHOR : Tong Qin <tong_qin@brown.edu>
//
// IfsLoader.cpp
//
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "tokenizer.h"
#include "IfsWrlLoader.h"

#define VRML_HEADER "#VRML V2.0 utf8"

const char* IfsWrlLoader::_ext = "wrl";

bool my_stof(string str, float & num){
    double temp;
    string::size_type idx;

   try{
        temp=stod(str, & idx);
    } catch (const std::invalid_argument& ia) {
      std::cerr << "Invalid argument: " << ia.what() << '\n';
      return false;
    }

    string redsidual=str.substr(idx);

    if(redsidual.length()>0){
        return false;
    } else {
        num=float(temp);
        return true;
    }
}

bool my_stoi(string str, int & num){
    string::size_type idx;

    try{
    num=stoi(str, & idx);
    }   catch(const std::invalid_argument & ia){
    cerr<<"Invalid argument: "<<ia.what()<<endl;
    return false;
}
    string redsidual=str.substr(idx);

    if(redsidual.length()>0)
        return false;
    else
        return true;        
}

bool checki(int num, const char * str){
    string num_str=to_string(num);
    if(num_str!=string(str)){
        cout<<num<<" "<<str<<endl;
        return false;
    } else return true;
}


int IfsWrlLoader::_load_point(Tokenizer & tokenizer, vector<float> * point_vector){
    if(!tokenizer.expecting("[")) 
        return -1;

    while(tokenizer.get() && tokenizer!="]"){
         float num;

         if(!my_stof(tokenizer, num))
            return -2; //number error
         else 
            point_vector->push_back(num);
    }

    if(tokenizer!="]")
        return -3; //missing ] or syntax error
           
    if(!tokenizer.expecting("}")) 
        return -4; //missing }
    return 1;
}

int IfsWrlLoader::_load_index(Tokenizer & tokenizer, vector<int> * vector){

    if(!tokenizer.expecting("[")) 
        return -1;
    
    while(tokenizer.get() && tokenizer!="]"){
        int num;
        if(!my_stoi(tokenizer, num))
            return -2;
        else 
            vector->push_back(num);
    }

    if(tokenizer!="]")
        return -3;

    return 1;
}

int IfsWrlLoader::_load_bool(Tokenizer & tokenizer, bool * boolVar){

    tokenizer.get();
    if(tokenizer=="FALSE"){
        * boolVar=false;
    } else if(tokenizer=="TRUE"){
        * boolVar=true;
    } else {
        return -5;//syntax error with bool variable;
    }

    return 1;
}

bool IfsWrlLoader::load(const char* filename, Ifs& ifs) {
  bool success = false;
  ifstream fileInput;

  if(filename!=(char*)0) {
    
    fileInput.open(filename, ifstream::in);
    if(!fileInput) 
    {
        cerr<<"error: unable to open input file: data.wrl"<<endl;
        return success;
    }

    char cstr[512];
    fileInput.getline(cstr, 512);
    
    string str(cstr);
       
    if(str!="#VRML V2.0 utf8\r")
    {
        cerr<<"error: the head of the .wrl file is wrong!"<<endl;
        fileInput.close();
        return success;
    }


    Tokenizer tokenizer(fileInput); 


    while(tokenizer.get() && tokenizer!="IndexedFaceSet");

    if(tokenizer!="IndexedFaceSet"){
         cerr<<"Error: No IndexedFaceSet is found here"<<endl;
         fileInput.close();
         return success;
    }

    //After the IndexedFaceSet is found
    //We need to further tokenize the IndexedFaceSet are
     while(tokenizer.get()){

    try{
        if(tokenizer=="coord"){
        
        try{ 
            if(!tokenizer.expecting("Coordinate")) throw ("Syntax Error: 'Coordinate'");
            if(!tokenizer.expecting("{")) throw ("Syntax Error: Coordinate missing {");
            if(!tokenizer.expecting("point")) throw("Syntax Error: 'point'");
        } catch(const char * error) {
            cerr<<string(error)<<endl;
            return success;
        }


        //Point

             vector<float> * tempCoord=& (ifs.getCoord());
             int flag=_load_point(tokenizer, tempCoord);
             // cout<<flag<<" "<<tempCoord<<endl;
             if(flag<0)
                throw(flag);
         
        //coord index            

        } else if(tokenizer=="coordIndex") {

            vector<int> * tempCoordIndex=& (ifs.getCoordIndex());
            int flag=_load_index(tokenizer, tempCoordIndex);
            if(flag<0)
                throw(flag);

        } else if(tokenizer=="ccw"){
        	bool * tempCcw=&(ifs.getCcw());
        	int flag=_load_bool(tokenizer, tempCcw);
            if(flag<0) throw(flag);
        } else if(tokenizer=="convex") {
        	bool * tempConvex=&(ifs.getConvex());
        	int flag=_load_bool(tokenizer,tempConvex);
            if(flag<0) throw(flag);

        } else if(tokenizer=="creaseAngle"){
        	float * tempCreaseAngle=&(ifs.getCreaseangle());
            float angle_num;
        	
            tokenizer.get();
        	if(!my_stof(tokenizer, angle_num)) 
                throw -2;
            else
        	   * tempCreaseAngle=angle_num;
        } else if(tokenizer=="solid"){
        	bool * tempSolid=&(ifs.getSolid());
        	int flag=_load_bool(tokenizer, tempSolid);
            if(flag<0) throw(flag);

        } else if(tokenizer=="colorPerVertex") {

        	tokenizer.get();
        	if(tokenizer=="FALSE"){
        		ifs.setColorPerVertex(false);
        	} else if(tokenizer=="TRUE"){
        		ifs.setColorPerVertex(true);
        	} else {
                cerr<<"Syntax error: colorPerVertex."<<endl;
                return success;
        	}

        } else if(tokenizer=="color") {
        	try{
                if(!tokenizer.expecting("Color")) throw("Syntax error: Color");
                if(!tokenizer.expecting("{")) throw ("Syntax error: Color missing {");
                if(!tokenizer.expecting("color")) throw ("Syntax error: color");
               
            } catch(const char * error){
                cerr<<string(error)<<endl;
                return success;
            }
            vector<float> * tempColor=& (ifs.getColor());            
        	int flag=_load_point(tokenizer,tempColor);
            if(flag<0) throw(flag);

        } else if(tokenizer=="colorIndex") {

            vector<int> * tempColorIndex=& (ifs.getColorIndex());
            int flag=_load_index(tokenizer, tempColorIndex);
            if(flag<0) throw(flag);

        } else if(tokenizer=="normalPerVertex") {
        	tokenizer.get();
        	if(tokenizer=="FALSE"){
        		ifs.setNormalPerVertex(false);
        	} else if(tokenizer=="TRUE"){
        		ifs.setNormalPerVertex(true);
        	} else {
        		cerr<<"Syntax error: normalPerVertex"<<endl;
                return success;
        	}

        } else if(tokenizer=="normal") {
        	try{
                if(!tokenizer.expecting("Normal")) throw("Syntax error: Normal");
                if(!tokenizer.expecting("{")) throw ("Syntax error: Color missing {");
                if(!tokenizer.expecting("normal")) throw ("Syntax error: normal");
            } catch(const char * error){
                cerr<<string(error)<<endl;
                return success;
            }

       		vector<float> * tempNormal=& (ifs.getNormal());
            int flag=_load_point(tokenizer, tempNormal);
            if(flag<0) throw (flag);

        } else if(tokenizer=="normalIndex"){
        	
            vector<int> * tempNormalIndex=& (ifs.getNormalIndex());
            int flag=_load_index(tokenizer, tempNormalIndex);
            if(flag<0) throw(flag);
        } else if(tokenizer=="texCoord"){

            try{
                if(!tokenizer.expecting("TextureCoordinate")) throw("Syntax error: TextureCoordinate");
                if(!tokenizer.expecting("{")) throw ("Syntax error: Color missing {");
                if(!tokenizer.expecting("point")) throw ("Syntax error: texture point");
            } catch(const char * error){
                cerr<<string(error)<<endl;
                return success;
            }
        	
        	vector<float> * tempTex=& (ifs.getTexCoord());
            int flag=_load_point(tokenizer, tempTex);
            if(flag<0) throw(flag);            

	 	} else if(tokenizer=="texCoordIndex") {
        	
            vector<int> * tempTexIndex=& (ifs.getTexCoordIndex());
            int flag=_load_index(tokenizer, tempTexIndex);
            if(flag<0) throw(flag);
        } else if(tokenizer=="}"){ 
        //have finished reading the IndexedFaceSet filed. Let us leave
            break;
        } 
    } catch(int error) {
            switch(error){
                case -1:
                    cerr<<"Syntax error: missing ["<<endl;
                    break;
                case -2:
                    cerr<<"Syntax error: wrong number"<<endl;
                    break;
                case -3:
                    cerr<<"Syntax error: missing ]"<<endl;
                    break;
                case -4:
                    cerr<<"Syntax error: missing }"<<endl;
                    break;
                default:
                    break;

            }  
            return success;  
        }//try

     }//while(get())
     if(tokenizer!="}"){
        cerr<<"Syntax Error: Not ending with '}'"<<endl;
        fileInput.close();
        return success;
    }

    success=true;
    fileInput.close();
  }//if(filename=0)
 
  return success;
}

