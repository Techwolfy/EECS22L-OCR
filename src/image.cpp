//Image.cpp

//Includes
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <gtkmm.h>
#include "image.h"

//Constructors
Image::Image() : Image(0, 0) {

}

Image::Image(int width, int height) : w(width),
									  h(height) {
	//Set initial sizes of vectors
	r.resize(h, std::vector<unsigned char>(w));
	g.resize(h, std::vector<unsigned char>(w));
	b.resize(h, std::vector<unsigned char>(w));
}

Image::Image(Glib::RefPtr<Gdk::Pixbuf> pixbuf) : w(pixbuf->get_width()),
												 h(pixbuf->get_height()) {
	//Set initial sizes of vectors
	r.resize(h, std::vector<unsigned char>(w));
	g.resize(h, std::vector<unsigned char>(w));
	b.resize(h, std::vector<unsigned char>(w));

	//Load pixbuf data into vectors
	guint8 *pixels = pixbuf->get_pixels();
	int pos = 0;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			r[i][j] = pixels[pos++];
			g[i][j] = pixels[pos++];
			b[i][j] = pixels[pos++];
			if(pixbuf->get_has_alpha()) {
				pos++;	//Skip the alpha byte if it's present
			}
		}
	}
}

//Destructor
Image::~Image() {

}

//Functions
//Get the width of the image
int Image::getWidth() {
	return w;
}

//Get the height of the image
int Image::getHeight() {
	return h;
}

//Create a Gdk::Pixbuf copy of the image
Glib::RefPtr<Gdk::Pixbuf> Image::getPixbuf() {
	guint8 *data = new guint8[w * h * 4];
	for(int i = 0; i < sizeof(data); i++) {
		data[i] = '\0';
	}

	int pos = 0;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			data[pos++] = r[i][j];
			data[pos++] = g[i][j];
			data[pos++] = b[i][j];
			data[pos++] = '\0';	//No alpha
		}
	}

	//Create and return pixbuf (takes ownership of data pointer)
	return Gdk::Pixbuf::create_from_data(data, Gdk::Colorspace::COLORSPACE_RGB, true, 8, w, h, w * 4, Gdk::Pixbuf::SlotDestroyData(&freePixbufByteArray));
}

//Free a byte array previously allocated in Image::getPixbuf()
//Note: static is required for sigc::mem_fun(), and consts are required for static, but the passed pointer is still modified (freed)
void Image::freePixbufByteArray(const guint8 *bytes) {
	delete[] bytes;
}

//Save the image to a file
int Image::save(std::string filename) {
	getPixbuf()->save(filename, "jpeg");
}

void Image::toBW() {
	unsigned int tmp;
	
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			tmp = (r[y][x] + g[y][x] + b[y][x]) / 3;
			r[y][x] = tmp;
			g[y][x] = tmp;
			b[y][x] = tmp;
		}
	}
}

//Image rotation by radian and rotation center
void Image::rotate(double radians, int offsetX, int offsetY) {
	std::vector<std::vector<unsigned char>> tempR;
	std::vector<std::vector<unsigned char>> tempG;
	std::vector<std::vector<unsigned char>> tempB;
	tempR.resize(h, std::vector<unsigned char>(w));
	tempG.resize(h, std::vector<unsigned char>(w));
	tempB.resize(h, std::vector<unsigned char>(w));

	int x = 0;
	int y = 0;
	int dX = 0;
	int dY = 0;
	double cosTheta = cos(radians);
	double sinTheta = sin(radians);

	for(int i = 0; i < w; i++) {
		for(int j = 0; j < h; j++) {
			tempR[j][i] = r[j][i];
			tempG[j][i] = g[j][i];
			tempB[j][i] = b[j][i];
			r[j][i] = 255;
			g[j][i] = 255;
			b[j][i] = 255;
		}
	}

	for(int i = 0; i < w; i++) {
		for(int j = 0; j < h; j++) {
			x = i - offsetX;
			y = j - offsetY;
			
			dX = round((x * cosTheta) + (y * sinTheta)) + offsetX;
			dY = round((-x * sinTheta) + (y * cosTheta)) + offsetY;
			if(dX >= 0 && dY >= 0 && dX < w && dY < h){
				r[dY][dX] = tempR[j][i];
				g[dY][dX] = tempG[j][i];
				b[dY][dX] = tempB[j][i];
			}
		}
	}	
}

//Crop image by 2 set of coordinate
void crop(int startX, int startY, int endX, int endY) {
	//TODO: Implement
}

//Print debug messages, if DEBUG flag is set
void Image::printDebug(const char *format, ...) {
#ifdef DEBUG
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
#endif
}
