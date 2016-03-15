//Test-PreProcessing.cpp
//Tests for preprocessing functions

//Includes
#include <stdio.h>
#include <assert.h>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <iostream>
#include "image.h"

//Load raw pixbuf resource at compile time
#include "helloworld.pixbuf"

int main(int argc, char *argv[]) {
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create image
	Image image(Gdk::Pixbuf::create_from_inline(sizeof(helloworld_pixbuf), helloworld_pixbuf));

	//Run preprocessing functions
	image.removeStains();
	image.toBW(185);
	std::vector<int> edge = image.findCropEdge();
	image.crop(edge[0], edge[1], edge[2], edge[3]);
	image.save("preprocessing-out-crop.jpg");
	image.rotate(7.5);
	image.save("preprocessing-out-rotate.jpg");

	printf("Image preprocessing test complete. CHECK OUTPUT FILE FOR RESULT!\n");
	return 0;
}
