#ifndef IMAGE_H
#define IMAGE_H

//Defines
#define SLEN 80 //Maximum length of file names

//Includes
#include <vector>
#include <gtkmm.h>

class Image {
public:
	//Constructors
	Image();
	Image(int width, int height);
	Image(Glib::RefPtr<Gdk::Pixbuf> pixbuf);

	//Destructor
	~Image();
	
	//Functions
	int getWidth();
	int getHeight();
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf();
	int save(std::string filename);
	void toBW();
	void rotate(double radians, int offsetX, int offsetY);
	void crop(int startX, int startY, int endX, int endY);

private:
	//Variables
	int w;
	int h;
	std::vector<std::vector<unsigned char>> r;
	std::vector<std::vector<unsigned char>> g;
	std::vector<std::vector<unsigned char>> b;

	//Functions
	void printDebug(const char *format, ...);
};

#endif	//IMAGE_H
