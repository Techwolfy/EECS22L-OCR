
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtkmm.h>
#include "../inc/image.h"
#include "square.pixbuf"
using namespace std;

/* print a menu */

//IMAGE ReadImage(const char *fname);



int main(int argc, char *argv[]) {
  //char	fname[SLEN];
//	char	fname2[SLEN];
  double radian;
  radian=-7.5*3.14159/180;
//	sprintf(fname,"../doc/helloworldslanted.jpg");
//	sprintf(fname2,"../doc/helloworldslantedtest.jpg");


	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create pixbuf
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_inline(sizeof(square_pixbuf), square_pixbuf);
	pixbuf->save("resout.jpg", "jpeg");

	//Test image pixbuf constructor
	Image image(pixbuf);
	assert(&image != NULL);

	

	image.StainRemoval();
	cout<<"StainRemoval operation is done"<<endl;
	image.toBW();
	cout<<"Black & White operation is done!"<<endl;
	image.rotate(radian,image.getWidth()/2,image.getHeight()/2);
	cout<<"rotate  operation is done!"<<endl;
// image.crop(350, 380, 1620, 1395);
  image.crop(0,0,50,50);
	cout<<"crop  operation is done!"<<endl;
	image.save("preprocessing.jpg");
	cout<<"image has been saved"<<endl;
    return 0;
}


/*** function definitions ***/
/* Read Image */
/*
IMAGE ReadImage(const char fname[SLEN])
{
    FILE           *File;
    char            Type[SLEN];
    int             W, H, MaxValue;
    int    x, y;
    char            SysCmd[SLEN * 5];
    char            ftype[] = ".ppm";
    char            fname_tmp[SLEN];  
    
    
    
    
    strcpy(fname_tmp, fname);
    
    sprintf(SysCmd, "jpegtopnm %s.jpg > %s.ppm",fname_tmp,fname_tmp);
    system(SysCmd);
    strcat(fname_tmp, ftype);
    
    File = fopen(fname_tmp, "r");
    if (!File) {
#ifdef DEBUG
        printf("\nCan't open file \"%s\" for reading!\n", fname);
#endif
        
    }
    
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
#ifdef DEBUG
        printf("\nUnsupported file format!\n");
#endif
        fclose(File);
        
    }
    
    fscanf(File, "%d", &W);
    
    if (W <= 0) {
#ifdef DEBUG
        printf("\nUnsupported image width %d!\n", W);
#endif
        fclose(File);
        
    }
    
    fscanf(File, "%d", &H);
    
    if (H <= 0) {
#ifdef DEBUG
        printf("\nUnsupported image height %d!\n", H);
#endif
        fclose(File);
        
    }
    
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
#ifdef DEBUG
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
#endif
        fclose(File);
        
    }
    if ('\n' != fgetc(File)) {
#ifdef DEBUG
        printf("\nCarriage return expected at the end of the file!\n");
#endif
        fclose(File);
        
    }
    
    IMAGE image(W, H);
    
    
    

    
    for (y = 0; y < image.HEIGHT; y++)
        for (x = 0; x < image.WIDTH; x++) {
            image.R[y][x]=fgetc(File);
            image.G[y][x]=fgetc(File);
            image.B[y][x]=fgetc(File);

            
        }

    
    if (ferror(File)) {
#ifdef DEBUG
        printf("\nFile error while reading from file!\n");
#endif
        image.~IMAGE();
        
    }
    
#ifdef DEBUG
    printf("%s was read successfully!\n", fname_tmp);
#endif
    fclose(File);
    sprintf(SysCmd, "rm %s",fname_tmp); 
    system(SysCmd);
    
    return image;
}
*/

