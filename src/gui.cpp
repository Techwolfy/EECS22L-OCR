//GUI.cpp

//Includes
#include <string>
#include <fstream>
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
			 imageData(Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, 385, 500)),
			 imageWidget(imageData) {
	
	//Set window details
	set_title("EECS22L-OCR v0.0.1-alpha");
	set_default_size(800, 500);

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

//Show a text input dialog
std::string GUI::showStringDialog(std::string message) {
	Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_OTHER);
	Gtk::Entry input;
	input.show();
	dialog.get_vbox()->add(input);
	//dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);	//OK button is in dialog by default
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if(dialog.run() == Gtk::RESPONSE_OK) {
		return input.get_text();
	} else {
		return "";
	}
}

//Show a number input dialog
double GUI::showNumberDialog(std::string message) {
	std::string result = showStringDialog(message);

	try {
		if(result != "") {
			return std::stod(result);
		}
	} catch(std::exception &e) {
		showErrorDialog(e.what());
	}

	return 0.0;
}

//Show a file input dialog
std::string GUI::showFileDialog(std::string message, Gtk::FileChooserAction type) {
	Gtk::FileChooserDialog dialog(message, type);
	dialog.set_transient_for(*this);
	dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	if(dialog.run() == Gtk::RESPONSE_OK) {
		return dialog.get_filename();
	} else {
		return "";
	}
}

//Show a text dialog
void GUI::showMessageDialog(std::string message) {
	Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_OTHER);
	dialog.run();
}

//Show an error dialog
void GUI::showErrorDialog(std::string error) {
	Gtk::MessageDialog dialog(*this, error, false, Gtk::MESSAGE_ERROR);
	dialog.run();
}

//Callbacks
//Load image from file
void GUI::onLoadImage() {
	std::string filename = showFileDialog("Please choose an image:", Gtk::FILE_CHOOSER_ACTION_OPEN);
	if(filename != "") {
		//Load image (RefPtr deletes previous image)
		try {
			imageData = Gdk::Pixbuf::create_from_file(filename, 500, 500, true);
			imageWidget.set(imageData);

			//Update tutorial text
			Glib::RefPtr<Gtk::TextBuffer> textData = Gtk::TextBuffer::create();
			textData->set_text("Use the functions in the Pre-Processing menu to clean up the image.\nThen use the functions in the OCR menu to convert it to text.\n");
			textView.set_buffer(textData);
		} catch(std::exception &e) {
			showErrorDialog(e.what());
		}
	}
}

//Save image to file
void GUI::onSaveImage() {
	std::string filename = showFileDialog("Please choose a filename:", Gtk::FILE_CHOOSER_ACTION_SAVE);
	if(filename != "") {
		//Add extension to filename if necessary
		if(filename.substr(filename.length() - 4, std::string::npos) != ".jpg") {
			filename.append(".jpg");
		}
		//Save image to JPEG file
		try {
			imageData->save(filename, "jpeg");
		} catch(std::exception &e) {
			showErrorDialog(e.what());
		}
	}
}

//Save text to file
void GUI::onSaveText() {
	std::string filename = showFileDialog("Please choose a filename:", Gtk::FILE_CHOOSER_ACTION_SAVE);
	if(filename != "") {
		//Save text to file
		try {
			std::fstream file;
			file.open(filename, std::fstream::out | std::fstream::trunc);
			file << textView.get_buffer()->get_text();
			file.flush();
			file.close();
		} catch(std::exception &e) {
			showErrorDialog(e.what());
		}
	}
}

//Close the program
void GUI::onClose() {
	hide();
}

//Rotate the image
void GUI::onRotateImage() {
	double degrees = showNumberDialog("Please enter the angle to rotate the image by, in degrees:");
	if(degrees != 0.0) {
		//TODO: Rotate image
		showMessageDialog(std::string("Rotation degrees: ") + std::to_string((long double)degrees));
	}
}

//Crop the image
void GUI::onCropImage() {
	std::string coordinates = showStringDialog("Please enter initial and final X and Y coordinates (comma separated; e.g. 0,0,100,100):");
	if(coordinates != "") {
		//TODO: Crop image
		showMessageDialog(std::string("Crop coordinates: ") + coordinates);
	}
}

//Run the OCR process on the image
void GUI::onOCR() {
	//TODO
}

//Run post proccesing on the OCRed text
void GUI::onPostProcess() {
	//TODO
}

//Display a brief description of the program
void GUI::onAbout() {
	showMessageDialog("About EECS22l-OCR\n\nVersion v0.0.1-alpha\n\nDeveloped By:\nDaniel Ring\nShahrooz Maghsoudi\nZunwen Li\nJinliang Liao\nMichael Andon\nDonghao Feng\nYixiang Yan\n");
}

//Display instructions for the program
void GUI::onHelp() {
	showMessageDialog("Please see the doc/OCR_UserManual.pdf file for usage information.\n");
}
