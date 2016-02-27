//GUI.cpp

//Includes
#include <gtkmm.h>
#include "gui.h"

//Constants
const char *GUI::uiXML ="<ui>"
						"	<menubar name='MenuBar'>"
						"		<menu action='MenuFile'>"
						"			<menuitem action='LoadImage'/>"
						"			<separator/>"
						"			<menuitem action='SaveImageAs'/>"
						"			<menuitem action='SaveTextAs'/>"
						"			<separator/>"
						"			<menuitem action='Close'/>"
						"		</menu>"
						"		<menu action='MenuPreProc'>"
						"			<menuitem action='RotateImage'/>"
						"			<menuitem action='CropImage'/>"
						"		</menu>"
						"		<menu action='MenuOCR'>"
						"			<menuitem action='RunOCR'/>"
						"		</menu>"
						"		<menu action='MenuPostProc'>"
						"			<menuitem action='PostProcessText'/>"
						"		</menu>"
						"		<menu action='MenuHelp'>"
						"			<menuitem action='Help'/>"
						"			<menuitem action='About'/>"
						"		</menu>"
						"	</menubar>"
						"</ui>";

//Constructor
GUI::GUI() : box(),
			 menuActionGroup(Gtk::ActionGroup::create()),
			 menuUIManager(Gtk::UIManager::create()) {
	//Set window details
	set_title("EECS22L-OCR v0.0.1-alpha");
	set_default_size(200, 200);	//TODO: Adjust this

	//Add an empty box to the window
	add(box);

	//Set up menu
	setupMenu();

	//Display the GUI
	box.show();
}

//Destructor
GUI::~GUI() {

}

//Functions
//Set up menus
void GUI::setupMenu() {
	//Set up menu actions
		//Icons: https://developer.gnome.org/gtkmm/2.24/namespaceGtk_1_1Stock.html
	menuActionGroup->add(Gtk::Action::create("MenuFile", "_File"));
	menuActionGroup->add(Gtk::Action::create("LoadImage", Gtk::Stock::OPEN, "Load Image"), sigc::mem_fun(*this, &GUI::onLoadImage));
	menuActionGroup->add(Gtk::Action::create("SaveImageAs", Gtk::Stock::SAVE_AS, "Save Image As..."), sigc::mem_fun(*this, &GUI::onSaveImage));
	menuActionGroup->add(Gtk::Action::create("SaveTextAs", Gtk::Stock::SAVE_AS, "Save Text As..."), sigc::mem_fun(*this, &GUI::onSaveText));
	menuActionGroup->add(Gtk::Action::create("Close", Gtk::Stock::CLOSE), sigc::mem_fun(*this, &GUI::onClose));
	menuActionGroup->add(Gtk::Action::create("MenuPreProc", "_Pre-Processing"));
	menuActionGroup->add(Gtk::Action::create("RotateImage", Gtk::Stock::ORIENTATION_PORTRAIT, "Rotate Image"), sigc::mem_fun(*this, &GUI::onRotateImage));
	menuActionGroup->add(Gtk::Action::create("CropImage", Gtk::Stock::PAGE_SETUP, "Crop Image"), sigc::mem_fun(*this, &GUI::onCropImage));
	menuActionGroup->add(Gtk::Action::create("MenuOCR", "_OCR"));
	menuActionGroup->add(Gtk::Action::create("RunOCR", Gtk::Stock::EXECUTE, "Run OCR"), sigc::mem_fun(*this, &GUI::onOCR));
	menuActionGroup->add(Gtk::Action::create("MenuPostProc", "_Post-Processing"));
	menuActionGroup->add(Gtk::Action::create("PostProcessText", Gtk::Stock::BOLD, "Post-Process Text"), sigc::mem_fun(*this, &GUI::onPostProcess));
	menuActionGroup->add(Gtk::Action::create("MenuHelp", "_Help"));
	menuActionGroup->add(Gtk::Action::create("Help", Gtk::Stock::HELP), sigc::mem_fun(*this, &GUI::onHelp));
	menuActionGroup->add(Gtk::Action::create("About", Gtk::Stock::ABOUT), sigc::mem_fun(*this, &GUI::onAbout));
	
	//Set up menu UI manager
	menuUIManager->insert_action_group(menuActionGroup);
	
	//Initialize keyboard shortcuts
	add_accel_group(menuUIManager->get_accel_group());

	//Build menu
	menuUIManager->add_ui_from_string(uiXML);	//TODO: try/catch?
	
	//Add menu to main window
	box.pack_start(*menuUIManager->get_widget("/MenuBar"), Gtk::PACK_SHRINK);
}

//Callbacks
void GUI::onLoadImage() {

}

void GUI::onSaveImage() {

}

void GUI::onSaveText() {

}

//Closes the program
void GUI::onClose() {
	hide();
}

void GUI::onRotateImage() {

}

void GUI::onCropImage() {

}

void GUI::onOCR() {

}

void GUI::onPostProcess() {

}

void GUI::onAbout() {

}

void GUI::onHelp() {

}
