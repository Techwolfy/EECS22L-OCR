//Test-Preprocessing.cpp
//Tests for preprocessing functions

//Includes
#include <stdio.h>
#include <assert.h>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "image.h"

//Load raw pixbuf resource at compile time
#include "helloworld.pixbuf"

int main(int argc, char *argv[]) {
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create image
	Image image(Gdk::Pixbuf::create_from_inline(sizeof(helloworld_pixbuf), helloworld_pixbuf));

	//Run preprocessing functinos
	image.removeStains();
	image.toBW(185);
	image.rotate(-7.5);
	image.crop(50, 50, 150, 100);
	image.save("preprocessing.jpg");

	printf("Image preprocessing test complete. CHECK OUTPUT FILE FOR RESULT!\n");
	return 0;
}
