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
	
	//Functions
	int getWidth();
	int getHeight();
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf();
	static void freePixbufByteArray(const guint8 *array);
	int save(std::string filename);
	void toBW();
	void rotate(double radians, int offsetX, int offsetY);
  void StainRemoval();
  void crop(int startX, int startY, int endX, int endY);
  unsigned char getR(int x, int y);
  unsigned char getG(int x, int y);
  unsigned char getB(int x, int y);
  void setR(int x, int y, unsigned char value);
  void setG(int x, int y, unsigned char value);
  void setB(int x, int y, unsigned char value);
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
