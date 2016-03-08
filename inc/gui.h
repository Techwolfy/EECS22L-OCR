#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <glibmm/refptr.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/widget.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/filechooserdialog.h>
#include "image.h"

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
	//Layout
	Gtk::VBox vbox;
	Gtk::HBox hbox;
	//Menu
	Glib::RefPtr<Gtk::ActionGroup> menuActionGroup;
	Glib::RefPtr<Gtk::UIManager> menuUIManager;
	Gtk::Widget *menuWidget;
	//Text Widget
	Gtk::TextView textView;
	Gtk::ScrolledWindow textWidget;
	//Image Widget
	Glib::RefPtr<Gdk::Pixbuf> imageData;
	Gtk::Image imageWidget;
	//OCR Image Data
	Glib::RefPtr<Gdk::Pixbuf> ocrImage;
	Glib::RefPtr<Gdk::Pixbuf> oldImage;

	//Functions
	void setupMenuWidget();
	void setupTextWidget();
	void setupImageWidget();
	void updateImage(Glib::RefPtr<Gdk::Pixbuf> image);
	std::string showStringDialog(std::string message);
	double showNumberDialog(std::string message);
	std::string showFileDialog(std::string message, Gtk::FileChooserAction type);
	void showMessageDialog(std::string message);
	void showErrorDialog(std::string error);

	//Callbacks
	void onLoadImage();
	void onSaveImage();
	void onSaveText();
	void onClose();
	void onRotateImage();
	void onCropImage();
	void onRemoveColor();
	void onRemoveStains();
	void onUndo();
	void onOCR();
	void onPostProcess();
	void onHelp();
	void onAbout();
};

#endif //GUI_H
