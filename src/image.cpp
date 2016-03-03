//Image.cpp

//Includes
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <gtkmm.h>
#include "../inc/image.h"
//using namespace std;
//Constructors
Image::Image() {

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

//Get value of a specific pixel
unsigned char Image::getPixel(int x, int y, PixelColor color) {
	if(w > x && h > y && x >= 0 && y >= 0) {
		if(color == R) {
			return r[y][x];
		} else if(color == G) {
			return g[y][x];
		} else if(color == B) {
			return b[y][x];
		}
	}
	return 0;
}

//Set value of a specific pixel
void Image::setPixel(int x, int y, PixelColor color, unsigned char value) {
	if(w > x && h > y && x >= 0 && y >= 0) {
		if(color == R) {
			r[y][x] = value;
		} else if(color == G) {
			g[y][x] = value;
		} else if(color == B) {
			b[y][x] = value;
		}
	}
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
			data[pos++] = '\xFF';	//No alpha (255 = solid color)
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

//Change the image color to black and white and remove some stain and winkle
Image* Image::toBW(unsigned char threshold /* = 20 */) {
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			if(((r[y][x] + g[y][x] + b[y][x]) / 3) < threshold) {
				r[y][x] = 0;
				g[y][x] = 0;
				b[y][x] = 0;
			} else {
				r[y][x] = 255;
				g[y][x] = 255;
				b[y][x] = 255;
			}
		}
	}

	return this;
}

//Image rotation by radian and rotation center
Image* Image::rotate(double radians, int offsetX, int offsetY) {
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

	return this;
}


//Crop image by 2 set of coordinate
Image* Image::crop(int startX, int startY, int endX, int endY){ 
	w = endX - startX + 1;
	h = endY - startY + 1;
	
	std::vector<std::vector<unsigned char>> tempR;
	std::vector<std::vector<unsigned char>> tempG;
	std::vector<std::vector<unsigned char>> tempB;
	tempR.resize(h, std::vector<unsigned char>(w));
	tempG.resize(h, std::vector<unsigned char>(w));
	tempB.resize(h, std::vector<unsigned char>(w));

	for(int y = startY, j = 0; y < endY; y++, j++) {
		for(int x = startX, i = 0; x < endX; x++, i++) {
				tempR[j][i] = r[y][x];
				tempG[j][i] = g[y][x];
				tempB[j][i] = b[y][x];
		}
	}

	r.clear();
	g.clear();
	b.clear();
	r.resize(h, std::vector<unsigned char>(w));
	g.resize(h, std::vector<unsigned char>(w));
	b.resize(h, std::vector<unsigned char>(w));

	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			r[y][x] = tempR[y][x];
			g[y][x] = tempG[y][x];
			b[y][x] = tempB[y][x];
		}
	}

	return this;
}

//Remove stains
Image* Image::removeStains() {
	double tmpA = 0.0;
	double tmpB = 0.0;
	double tmpC = 0.0;

	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			if(r[y][x] > 160 && (r[y][x] - b[y][x]) > 20 && (r[y][x] - g[y][x]) > 16) {
				r[y][x] = 255;
				g[y][x] = 255;
				b[y][x] = 255;
			}

			tmpA = r[y][x] - g[y][x];
			tmpB = r[y][x] - b[y][x];
			tmpC = g[y][x] - b[y][x];
		
			if(abs(tmpA) > 50 || abs(tmpB) > 50 || abs(tmpC) > 50) {
				r[y][x] = 255;
				g[y][x] = 255;
				b[y][x] = 255;
			}
		}	
	}

	return this;
}
