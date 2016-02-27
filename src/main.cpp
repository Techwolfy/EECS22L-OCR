#include <gtkmm.h>
#include "gui.h"

int main(int argc, char *argv[]) {
	//Set up the GtkMM graphics interface
	Gtk::Main graphicsMain(argc, argv);

	//Create the GUI object
	GUI gui;

	//Delegate all further processing to the GUI
	Gtk::Main::run(gui);

	return 0;
}
