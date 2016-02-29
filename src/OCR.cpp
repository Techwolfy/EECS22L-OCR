
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/Image.h"
using namespace std;


/* print a menu */
void PrintMenu();
IMAGE ReadImage(const char *fname);



int  main()
{
    /*
     * Two dimensional arrays to hold the current image data. One array
     * for each color component
     */
    IMAGE image;
    int degree;
    double radian;
    
    
    
    char	fname[SLEN];
    int	choice;
    
    PrintMenu();
    cout<<"Please make your choice: ";
    cin>>choice;
    
    while (choice != 5) {
        switch (choice) {
            case 1:
                cout<<"Please input the file name to load: ";
                cin>> fname;
                
                image= ReadImage(fname);
                
                //cout << "sizeofR: " << image.R << endl;
                break;
            case 2:
                cout<<"Please input the file name to save: ";
                cin>> fname;
                
                image.SaveImage(fname);
                
                break;
            case 3:
                image.BlackNWhite();
                cout<<"\"Black & White\" operation is done!\n";
                break;
            case 4:
                cout<<"input degree";
                cin>>degree;
                radian = degree*3.1415926/180;
                image.rotate(radian,image.WIDTH/2,image.HEIGHT/2);
                break;
                
            default:
                cout<<"Invalid selection!\n";
                break;
        }
        
        PrintMenu();
        cout<<"Please make your choice: ";
        cin>> choice;
    }
    
    
    return 0;
}

/* print a menu */
void PrintMenu()
{
    cout<<"--------------------------------\n";
    cout<<" 1:  Load a JPG image\n";
    cout<<" 2:  Save an image in PPM and JPEG format\n";
    cout<<" 3:  Change a color image to Black & White\n";
    cout<<" 4:  rotate image\n";
    cout<<" 5:  Exit\n";
}
/*** function definitions ***/
/* Read Image */
IMAGE ReadImage(const char fname[SLEN])
{
    FILE           *File;
    char            Type[SLEN];
    int             W, H, MaxValue;
    int    x, y;
    char            SysCmd[SLEN * 5];
    char            ftype[] = ".ppm";
    char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
    
    
    
    
    strcpy(fname_tmp, fname);
    
    sprintf(SysCmd, "jpegtopnm %s.jpg > %s.ppm",fname_tmp,fname_tmp);
    system(SysCmd);
    strcat(fname_tmp, ftype);
    
    File = fopen(fname_tmp, "r");
    if (!File) {
#ifdef DEBUG
        printf("\nCan't open file \"%s\" for reading!\n", fname);
#endif
        //	return NULL;
    }
    
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
#ifdef DEBUG
        printf("\nUnsupported file format!\n");
#endif
        fclose(File);
        //	return NULL;
    }
    
    fscanf(File, "%d", &W);
    
    if (W <= 0) {
#ifdef DEBUG
        printf("\nUnsupported image width %d!\n", W);
#endif
        fclose(File);
        //	return NULL;
    }
    
    fscanf(File, "%d", &H);
    
    if (H <= 0) {
#ifdef DEBUG
        printf("\nUnsupported image height %d!\n", H);
#endif
        fclose(File);
        //	return NULL;
    }
    
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
#ifdef DEBUG
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
#endif
        fclose(File);
        //	return NULL;
    }
    if ('\n' != fgetc(File)) {
#ifdef DEBUG
        printf("\nCarriage return expected at the end of the file!\n");
#endif
        fclose(File);
        //	return NULL;
    }
    
    IMAGE image(W, H);
    
    
    
    /*	if (image=NULL)) {
     #ifdef DEBUG
     printf("\nError creating image from %s!\n", fname_tmp);
     #endif
     image.~IMAGE();
     fclose(File);
     return NULL;
     }
     */
    //else {
    
    for (y = 0; y < image.HEIGHT; y++)
        for (x = 0; x < image.WIDTH; x++) {
            image.R[y][x]=fgetc(File);
            image.G[y][x]=fgetc(File);
            image.B[y][x]=fgetc(File);
            
        }
    int test= (int)image.G[45][29];
    cout<<test<<endl;
    
    if (ferror(File)) {
#ifdef DEBUG
        printf("\nFile error while reading from file!\n");
#endif
        image.~IMAGE();
        //	return nullptr;
    }
    
#ifdef DEBUG
    printf("%s was read successfully!\n", fname_tmp);
#endif
    fclose(File);
    sprintf(SysCmd, "rm %s",fname_tmp); 
    system(SysCmd);//delete temp file
    
    return image;
    //}
}

//character cropping function
/*void charCrop(IMAGE image){
	int wImg = image.WIDTH;
	int hImg = image.HEIGHT;
	
	int cwImg = wImg/30;
	int chImg = hImg/46;

	int countWidth = cwImg;
	int countHeight = chImg;
	
	IMAGE imgList[cwImg][chImg];
	for(int x=0; x<cwImg; x++){
		for(int y=0; y<chImg; y++){
			IMAGE img = new IMAGE;
			img.WIDTH = countWidth;
			img.HEIGHT = countHeight;
			img.R = image.R;
			img.G = image.G;
			img.B = image.B;
		
			imgList[x][y] = img;
			countWidth = cwImg + countWidth;
		}
	}
	countHeight = chImg + countHeight;
}*/
