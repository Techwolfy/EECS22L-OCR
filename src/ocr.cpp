//OCR.cpp

//Includes
#include <vector>
#include <string>
#include "image.h"
#include "ocr.h"

//Constructor
OCR::OCR(){

}

//Desrtructor
OCR:~OCR(){

}

//Functions

void OCR::charCrop(IMAGE im, vector<vector<char> > &charVec){

  IMAGE newImage;
  vector<char> text;
  vector<unsigned char> TempR,TempG,TempB;
  for(int i=0; i<im.HEIGHT; i+=56){
    for(int j=0;j<im.WIDTH; j+=30){
      for(int m=0;m<56;m++){
        for(int n=0;n<30;n++){
          TempR.push_back(im.R[m+i][n+j]);
          TempG.push_back(im.G[m+i][n+j]);
          TempB.push_back(im.B[m+i][n+j]);
        }
        newImage.R.push_back(TempR);
        newImage.G.push_back(TempG);
        newImage.B.push_back(TempB);
        TempR.clear();
        TempG.clear();
        TempB.clear();
      }
          newImage.WIDTH=30;
          newImage.HEIGHT=56;
          text.push_back(charComp(newImage));
          newImage.R.clear();
          newImage.G.clear();
          newImage.B.clear();
    }
    charVec.push_back(text);
    text.clear();
  }
}

char OCR::charComp(IMAGE im){

  char output;
  float intensity;
  float refInt, difference, best=255.0;
  string line,value;
  intensity = avgInt(im); 
  ifstream reference ("averageIntensities.txt");
  if(reference.is_open()){
   while(getline (reference,line)){
   value = line.substr(0,7);
   refInt = atof(value.c_str());
   difference = (refInt-intensity> 0) ? (refInt-intensity) : (intensity - refInt);
   cout << difference;
   if(difference < best) {
     best = difference;
     output = line[7];
   }
     }
     reference.close();
   }
   cout << "The best value is : \n" << best << endl;
   cout << "The intensity value is : \n" << intensity << endl;
   return output;
 }
 
float OCR::avgInt(IMAGE im){

  float total = 0.0;
  int i,j;
  
  for(i=0; i<im.HEIGHT; i++){
    for(j=0;j<im.WIDTH;j++){
      total += im.R[i][j] + im.G[i][j] + im.B[i][j];
    }
  }
  
  return total/(3*1680.0);
}
