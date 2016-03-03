//Test-Preprocessing.cpp
//Tests for preprocessing functions

//Includes
#include <stdio.h>
#include <assert.h>
#include <gtkmm.h>
#include "image.h"

//Load raw pixbuf resource at compile time
#include "square.pixbuf"

int main(int argc, char *argv[]) {
	double radian = -7.5 * 3.14159 / 180;

	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create image
	Image image(Gdk::Pixbuf::create_from_inline(sizeof(square_pixbuf), square_pixbuf));

	//Run preprocessing functinos
	image.removeStains();
	image.toBW();
	image.rotate(radian, image.getWidth() / 2, image.getHeight() / 2);
	image.crop(0, 0, 50, 50);
	image.save("preprocessing.jpg");

	printf("Image preprocessing test complete. CHECK OUTPUT FILE FOR RESULT!\n");
	return 0;
}
