//Test-OCR.cpp
//Test for OCR functions

//Includes
#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "image.h"
#include "ocr.h"
#include "helloworld.pixbuf"

int main(int argc, char *argv[]) {
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);
	
	//Create images from reference 
	Image inputImage(Gdk::Pixbuf::create_from_inline(sizeof(helloworld_pixbuf), helloworld_pixbuf));
	
	//Convert HelloWorld Image to black and white 
	inputImage.toBW();

	//Perform OCR Functions
	OCR ocrImage(inputImage);
	std::fstream file;
	file.open("ocr-out.txt", std::fstream::out | std::fstream::trunc);
	file << ocrImage.recognize();
	file.flush();
	file.close();
		
	printf("OCR test complete. CHECK OUTPUT FILE FOR RESULT!\n");
	return 0;
}
