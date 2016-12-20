//Test-GUI.cpp
//Test for basic GUI functions.

//Includes
#include <stdio.h>
#include <assert.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include "gui.h"

//Load raw pixbuf resources at compile time
#include "square.pixbuf"
#include "helloworld.pixbuf"

int main(int argc, char *argv[]) {
	//Set up GtkMM
	Gtk::Main graphicsMain(argc, argv);

	//Create the GUI object
	GUI gui;

	//Show test prompt
	Gtk::MessageDialog dialog(gui, "Please verify that the GUI is displayed correctly, then close it and click OK.", false, Gtk::MESSAGE_OTHER);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.show();

	//Display the GUI for verification
	Gtk::Main::run(gui);

	//Determine test result
	if(dialog.run() == Gtk::RESPONSE_CANCEL) {
		printf("GUI test FAILED!\n");
		assert(false);
	}

	printf("GUI test successful!\n");
	return 0;
}
