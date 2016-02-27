#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>

class GUI : public Gtk::Window {
public:
	//Constructor
	GUI();

	//Destructor
	virtual ~GUI();

private:
	//Constants
	static const char *uiXML;

	//Variables
	Gtk::VBox box;
	Glib::RefPtr<Gtk::ActionGroup> menuActionGroup;
	Glib::RefPtr<Gtk::UIManager> menuUIManager;

	//Functions
	void setupMenu();

	//Callbacks
	void onLoadImage();
	void onSaveImage();
	void onSaveText();
	void onClose();
	void onRotateImage();
	void onCropImage();
	void onOCR();
	void onPostProcess();
	void onHelp();
	void onAbout();
};

#endif //GUI_H
