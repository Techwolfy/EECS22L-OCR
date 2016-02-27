/*********************************************************************/
/* Image.c: source code for image class	                             */

/*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../inc/Image.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
using namespace std;

IMAGE::IMAGE(){
    WIDTH=0;
    HEIGHT=0;
}

IMAGE::IMAGE(int w, int h){
    WIDTH=w;
    HEIGHT=h;
    R.resize(HEIGHT,vector<unsigned char>(WIDTH));
    
    G.resize(HEIGHT,vector<unsigned char>(WIDTH));
    
    B.resize(HEIGHT,vector<unsigned char>(WIDTH));
    
}

IMAGE::~IMAGE(void){
    R.clear();
    G.clear();
    B.clear();
}



int IMAGE::SaveImage(const char fname[SLEN])
{
    FILE           *File;
    int             x, y;
    char            SysCmd[SLEN * 5];
    
    char            ftype[] = ".ppm";
    char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
    char            fname_tmp2[SLEN];
    
    
    strcpy(fname_tmp, fname);
    strcpy(fname_tmp2, fname);
    strcat(fname_tmp2, ftype);
    
    File = fopen(fname_tmp2, "w");
    if (!File) {
#ifdef DEBUG
        printf("\nCan't open file \"%s\" for writing!\n", fname);
#endif
        return 1;
    }
    
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");
    
    
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++) {
            
            fputc((int)R[y][x], File);
            
            fputc((int)G[y][x], File);
            
            fputc((int)B[y][x], File);
            
        }
    
    if (ferror(File)) {
#ifdef DEBUG
        printf("\nError while writing to file!\n");
#endif
        return 2;
    }
    fclose(File);
#ifdef DEBUG
    printf("%s was saved successfully. \n", fname_tmp2);
#endif
    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "pnmtojpeg -rgb %s > %s.jpg",fname_tmp2,fname_tmp);
    if (system(SysCmd) != 0) {
#ifdef DEBUG
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
#endif
        return 3;
    }
#ifdef DEBUG
    printf("%s.jpg was stored for viewing. \n", fname_tmp);
#endif
    sprintf(SysCmd, "rm %s",fname_tmp2);
    system(SysCmd);//delete temp file
    return (0);
}





void IMAGE::BlackNWhite()
{
    int x, y;
    unsigned int tmp;
    
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x <WIDTH; x++) {
            tmp = (R[y][x] +G[y][x] + B[y][x]) / 3;
            R[y][x]=tmp;
            R[y][x]=tmp;  
            R[y][x]=tmp;   
        }
    }
}

/*---------------------add Feb 27 Jinliang Liao---------------------------------------*/
/*rotate image by radian */
void IMAGE::rotate(double radians,int offsetX, int offsetY){
    
    vector<vector<unsigned char> > tempR;
    vector<vector<unsigned char> > tempG;
    vector<vector<unsigned char> > tempB;
    tempR.resize(HEIGHT,vector<unsigned char>(WIDTH));
    tempG.resize(HEIGHT,vector<unsigned char>(WIDTH));
    tempB.resize(HEIGHT,vector<unsigned char>(WIDTH));
    
    
    int i,j,x,y,dX,dY;
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);
    
    
    for (i=0; i<WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            tempR[j][i] = R[j][i];
            tempG[j][i] = G[j][i];
            tempB[j][i] = B[j][i];
            R[j][i] = 255;
            G[j][i] = 255;
            B[j][i] = 255;
            
            
        }
    }
    
    for (i =0; i< WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            x = i -offsetX;
            y = j -offsetY;
            
            dX= round(x*cosTheta + y*sinTheta)+offsetX;
            dY= round(-x*sinTheta + y*cosTheta)+offsetY;
            if(dX>=0 && dY>=0 && dX<WIDTH && dY<HEIGHT){
                R[dY][dX] = tempR[j][i];
                G[dY][dX] = tempG[j][i];
                B[dY][dX] = tempB[j][i];
                
            }
        }
    }
    
    tempR.clear();
    tempG.clear();
    tempB.clear();
    
    
}



/* EOF Image.c */