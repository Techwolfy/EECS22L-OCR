//Main.cpp

//Includes
#include <iostream>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "gui.h"
#include "image.h"
#include "ocr.h"

//Program entry point
int main(int argc, char *argv[]) {
	//Set up the GtkMM graphics interface
	Gtk::Main graphicsMain(argc, argv);

	//Mode select
	if(argc >= 2) {	//CLI Mode
		//Load image from file
		Image ocrImage(Gdk::Pixbuf::create_from_file(argv[1]));
	
		//Clean up image and convert to black and white and 
		ocrImage.removeStains();
		ocrImage.toBW();
	
		//Auto crop image
		std::vector<int> crop = ocrImage.findCropEdge();
		Glib::RefPtr<Gdk::Pixbuf> ocrPixbuf = Gdk::Pixbuf::create_subpixbuf(ocrImage.getPixbuf(), crop[0], crop[1], crop[2] - crop[0], crop[3] - crop[1]);
	
		//Run OCR on cropped image and print the text to stdout
		std::cout << OCR(Image(ocrPixbuf)).recognize() << std::endl;
	} else {	//GUI Mode
		//Create the GUI object
		GUI gui;

		//Delegate all further processing to the GUI
		Gtk::Main::run(gui);
	}

	return 0;
}
