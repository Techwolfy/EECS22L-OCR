//Test-ImagePixbuf.cpp
//Test for Gdk::Pixbuf <-> Image conversion

//Includes
#include <stdio.h>
#include <assert.h>
#include <gtkmm/main.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "image.h"

//Load raw pixbuf resources at compile time
#include "square.pixbuf"
#include "helloworld.pixbuf"

int main(int argc, char *argv[]) {
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create pixbuf
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_inline(sizeof(square_pixbuf), square_pixbuf);
	pixbuf->save("imagepixbuf-in.jpg", "jpeg");

	//Test image pixbuf constructor
	Image image(pixbuf);
	assert(&image != NULL);

	//Test image conversion
	Glib::RefPtr<Gdk::Pixbuf> imagePixbuf = image.getPixbuf();
	assert(imagePixbuf->get_width() == image.getWidth());
	assert(imagePixbuf->get_height() == image.getHeight());
	imagePixbuf->save("imagepixbuf-out.jpg", "jpeg");

	//Test hello world image containing text
	Glib::RefPtr<Gdk::Pixbuf> textPixbuf = Gdk::Pixbuf::create_from_inline(sizeof(helloworld_pixbuf), helloworld_pixbuf);
	textPixbuf->save("imagepixbuf-text-in.jpg", "jpeg");
	Image(textPixbuf).getPixbuf()->save("imagepixbuf-text-out.jpg", "jpeg");

	//TODO: Diff output files; they should be identical

	printf("Image to Pixbuf conversion test complete. CHECK OUTPUT FILE FOR RESULT!\n");
	return 0;
}
