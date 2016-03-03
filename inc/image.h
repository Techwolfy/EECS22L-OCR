#ifndef IMAGE_H
#define IMAGE_H

//Includes
#include <vector>
#include <string>
#include <gtkmm.h>

class Image {
public:
	//Constructors
	Image();
	Image(int width, int height);
	Image(Glib::RefPtr<Gdk::Pixbuf> pixbuf);

	//Destructor
	~Image();

	//Enums
	enum PixelColor {R, G, B};
	
	//Functions
	int getWidth();
	int getHeight();
	unsigned char getPixel(int x, int y, PixelColor color);
	void setPixel(int x, int y, PixelColor color, unsigned char value);
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf();
	static void freePixbufByteArray(const guint8 *array);
	int save(std::string filename);
	void toBW(unsigned char threshold = 20);
	void rotate(double radians, int offsetX, int offsetY);
	void crop(int startX, int startY, int endX, int endY);
	void removeStains();

private:
	//Variables
	int w;
	int h;
	std::vector<std::vector<unsigned char>> r;
	std::vector<std::vector<unsigned char>> g;
	std::vector<std::vector<unsigned char>> b;
};

#endif	//IMAGE_H
