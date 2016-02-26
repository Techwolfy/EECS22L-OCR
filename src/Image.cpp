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

/* EOF Image.c */
