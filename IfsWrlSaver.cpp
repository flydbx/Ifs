// AUTHOR : Your Name <your_email@brown.edu>
//
// IfsWrlSaver.cpp
//

#include "IfsWrlSaver.h"

using namespace std;

const char* IfsWrlSaver::_ext = "wrl";

bool IfsWrlSaver::save(const char* filename, Ifs& ifs) {


  bool success = false;
  if(filename!=(char*)0) {
  	ofstream fileOutput;
    
    fileOutput.open(filename,ifstream::trunc);

    if(!fileOutput) 
    {
        cerr<<"error: unable to open output file: output.wrl"<<endl;
        return success;
    }



    fileOutput<<"#VRML V2.0 utf8\n Shape {\n geometry IndexedFaceSet {\n";

    //output coord
    {
        fileOutput<<"coord Coordinate {\n";

        fileOutput<<"point [\n";

        vector<float> point=ifs.getCoord();

        vector<float>::iterator iter=point.begin();
        while(iter!=point.end()){
            fileOutput<<* (iter++)<<'\t'<<*(iter++)<<'\t'<<*(iter++)<<endl;
        }

        fileOutput<<"]\n";

        fileOutput<<"}\n";
        cout<<"Save: done with the coord !"<<endl;
    }
 
   
    //output coordindex
    {

        fileOutput<<"coordIndex [\n";

        vector<int> coordIndex=ifs.getCoordIndex();

        vector<int>::iterator iter=coordIndex.begin();
        while(iter!=coordIndex.end()){
            if(*iter!=-1)
                fileOutput<<* iter<<'\t';
            else
                fileOutput<< * iter<<endl;
            iter++;
        }

        fileOutput<<"]\n";


        cout<<"Save: done with the coordIndex !"<<endl;


    }



     //output color
    vector<float> color=ifs.getColor();
        if(color.size()){
            fileOutput<<"color Color {\n";
            fileOutput<<"color [\n";
                 
            vector<float>::iterator iter=color.begin();
            while(iter!=color.end()){
                fileOutput<<* (iter++)<<'\t'<<*(iter++)<<'\t'<<*(iter++)<<endl;
            }

            fileOutput<<"]\n";

            fileOutput<<"}\n";

            //colorPerVertex
           
            {    
                bool colorpervert=ifs.getColorPerVertex();
                if(colorpervert)
                    fileOutput<<"colorPerVertex"<<'\t'<<"TRUE"<<endl;
                else
                    fileOutput<<"colorPerVertex"<<'\t'<<"FALSE"<<endl;
            }
            cout<<"Save: done with the color!"<<endl;


        }
     
   
    //output coordindex
    vector<int> colorIndex=ifs.getColorIndex();
    if(colorIndex.size()){

        fileOutput<<"colorIndex [\n";        

        vector<int>::iterator iter=colorIndex.begin();
        while(iter!=colorIndex.end()){
            if(*iter!=-1)
                fileOutput<<* iter<<'\t';
            else
                fileOutput<< * iter<<endl;
            iter++;
        }

        fileOutput<<"]\n";
        cout<<"Save: done with the colorIndex !"<<endl;
    }



    //output normal
    vector<float> normal=ifs.getNormal();

    if(normal.size()){
        fileOutput<<"normal Normal {\n";

        fileOutput<<"normal [\n";

        vector<float>::iterator iter=normal.begin();
        while(iter!=normal.end()){
            fileOutput<<* (iter++)<<'\t'<<*(iter++)<<'\t'<<*(iter++)<<endl;
        }

        fileOutput<<"]\n";

        fileOutput<<"}\n";


        //normalPerVertex
         {    
            bool normalpervert=ifs.getNormalPerVertex();
            if(normalpervert)
                fileOutput<<"normalPerVertex"<<'\t'<<"TRUE"<<endl;
            else
                fileOutput<<"normalPerVertex"<<'\t'<<"FALSE"<<endl;
        }

        cout<<"Save: done with the normal!"<<endl;
    }
 
    //output normalindex
    vector<int> normalIndex=ifs.getNormalIndex();
    if(normalIndex.size()){

        fileOutput<<"normalIndex [\n";

      
        vector<int>::iterator iter=normalIndex.begin();
        while(iter!=normalIndex.end()){
            if(*iter!=-1)
                fileOutput<<* iter<<'\t';
            else
                fileOutput<< * iter<<endl;
            iter++;
        }

        fileOutput<<"]\n";
    cout<<"Save: done with the normalIndex !"<<endl;

    }


    //output texture

    vector<float> texcoord=ifs.getTexCoord();

    if(texcoord.size()>0){
        fileOutput<<"texCoord TextureCoordinate {\n";

        fileOutput<<"point [\n";

        vector<float>::iterator iter=texcoord.begin();
        while(iter!=texcoord.end()){
            fileOutput<<* (iter++)<<'\t';
        }
        fileOutput<<"\n";
        fileOutput<<"]\n";
        fileOutput<<"}\n";



        cout<<"Save: done with the TexCoord!"<<endl;
    }
 
    //output normalindex
    vector<int> TexCoordIndex=ifs.getTexCoordIndex();
    if(TexCoordIndex.size()){

        fileOutput<<"texCoordIndex [\n";

      
        vector<int>::iterator iter=TexCoordIndex.begin();
        while(iter!=TexCoordIndex.end()){
            if(*iter!=-1)
                fileOutput<<* iter<<'\t';
            else
                fileOutput<< * iter<<endl;
            iter++;
        }

        fileOutput<<"]\n";
    cout<<"Save: done with the TexCoordIndex !"<<endl;

    }

    //output ccw
    {    
        bool ccw=ifs.getCcw();
        if(ccw)
            fileOutput<<"ccw"<<'\t'<<"TRUE"<<endl;
        else
            fileOutput<<"ccw"<<'\t'<<"FALSE"<<endl;
    } 

    //output convex

    {    
        bool convex=ifs.getConvex();
        if(convex)
            fileOutput<<"convex"<<'\t'<<"TRUE"<<endl;
        else
            fileOutput<<"convex"<<'\t'<<"FALSE"<<endl;
    } 

    //output solid
    {    
        bool solid=ifs.getSolid();
        if(solid)
            fileOutput<<"solid"<<'\t'<<"TRUE"<<endl;
        else
            fileOutput<<"solid"<<'\t'<<"FALSE"<<endl;
    } 

    //output crease angle
    {    
        float creaseAngle=ifs.getCreaseangle();
        fileOutput<<"creaseAngle"<<'\t'<<creaseAngle<<endl;
    } 

    fileOutput<<"}\n}\n";
    fileOutput.close();
    success=true;
  }
  return success;
}

