//test-ocr.cpp
//Test for OCR functions
#include <stdio.h>
#include <assert.h>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "image.h"
#include "ocr.h"
#include "helloworld.pixbuf"


int main(int argc, char *argv[]){
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);
	
	//Create images from reference 
	Image inputImage(Gdk::Pixbuf::create_from_inline(sizeof(helloworld_pixbuf), helloworld_pixbuf));
	//Image refImage(Gdk::Pixbuf::create_from_inline(sizeof(couriernew_pixbuf), couriernew_pixbuf));
	
	//Convert HelloWorld Image to black and white 
	inputImage.toBW(20);

	//Perform OCR Functions
	OCR ocrImage(inputImage);
	ocrImage.recognize();
		
	printf("OCR test complete.\n");
	return 0;
	

}
