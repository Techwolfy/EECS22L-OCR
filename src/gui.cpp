//GUI.cpp

//Includes
#include <stdio.h>
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
GUI::GUI() : vbox(),
			 hbox(),
			 menuActionGroup(Gtk::ActionGroup::create()),
			 menuUIManager(Gtk::UIManager::create()),
			 textView(),
			 textWidget(),
			 imageData(Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, 200, 200)),
			 imageWidget(imageData) {
	
	//Set window details
	set_title("EECS22L-OCR v0.0.1-alpha");
	set_default_size(400, 200);	//TODO: Adjust this

	//Set up layout boxes
	hbox.set_border_width(10);
	hbox.set_spacing(10);

	//Set up menu, image container, and text editor
	setupMenuWidget();
	setupImageWidget();
	setupTextWidget();

	//Add UI elements to the layout boxes
	add(vbox);
	vbox.pack_start(*menuWidget, Gtk::PACK_SHRINK);
	vbox.pack_start(hbox, Gtk::PACK_SHRINK);
	hbox.pack_start(imageWidget, Gtk::PACK_SHRINK);
	hbox.pack_end(textWidget, Gtk::PACK_EXPAND_WIDGET);

	//Display the GUI
	vbox.show();
	hbox.show();
	show();
}

//Destructor
GUI::~GUI() {

}

//Functions
//Set up menus
void GUI::setupMenuWidget() {
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

	//Build and enable menu
	menuUIManager->add_ui_from_string(uiXML);
	menuWidget = menuUIManager->get_widget("/MenuBar");
	menuWidget->show();
}

//Set up text box
void GUI::setupTextWidget() {
	textWidget.add(textView);
	textWidget.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	textWidget.show();

	//Add initial text
	Glib::RefPtr<Gtk::TextBuffer> textData = Gtk::TextBuffer::create();
	textData->set_text("Please select an image to process.\n");
	textView.set_buffer(textData);
	textView.show();
}

//Set up blank image
void GUI::setupImageWidget() {
	imageWidget.set(imageData);
	imageWidget.show();
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
