//Image.cpp

//Includes
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
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

Image::Image(Glib::RefPtr<Gdk::Pixbuf> pixbuf) : w(pixbuf.get_width()),
												 h(pixbuf.get_height()) {
	//Set initial sizes of vectors
	r.resize(h, std::vector<unsigned char>(w));
	g.resize(h, std::vector<unsigned char>(w));
	b.resize(h, std::vector<unsigned char>(w));

	//Load pixbuf data into vectors
	guint8 *pixels = pixbuf.get_pixels();
	int pos = 0;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			r[i][j] = pixels[pos++];
			g[i][j] = pixels[pos++];
			b[i][j] = pixels[pos++];
		}
	}
}

//Destructor
Image::~Image() {

}

//Functions
//Create a Gdk::Pixbuf copy of the image
Glib::RefPtr<Gdk::Pixbuf> getPixbuf() {
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
	guint8 *data = new guint8[w * h * 3];
	int pos = 0;

	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			data[pos++] = r[i][j];
			data[pos++] = g[i][j];
			data[pos++] = b[i][j];
		}
	}

	pixbuf = Gdk::Pixbuf::create_from_data(data, Gdk::Colorspace::COLORSPACE_RGB, false, 8, w, h, 0);
	delete[] data;
}

//Save the image to a file
int Image::save(std::string filename) {
	FILE *file;
	std::string command;
	std::string tmpfile;
	tmpfile = filename;
	
	file = fopen(tmpfile.c_str(), "w");
	if(!file) {
		printDebug("\nCan't open file \"%s\" for writing!\n", filename.c_str());
		return 1;
	}
	
	fprintf(file, "P6\n");
	fprintf(file, "%d %d\n", w, h);
	fprintf(file, "255\n");

	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			fputc(r[y][x], file);
			fputc(g[y][x], file);
			fputc(b[y][x], file);
		}
	}
	
	if(ferror(file)) {
		printDebug("\nError while writing to file!\n");
		return 2;
	}
	fclose(file);
	printDebug("%s.ppm was saved successfully. \n", tmpfile.c_str());
	
	//Convert file to jpeg
	command = std::string("pnmtojpeg -rgb ") + tmpfile + std::string(".ppm > ") + filename + std::string(".jpg");
	//TODO: Bad practice! Remove system() calls.
	if(system(command.c_str()) != 0) {
		printDebug("\nError while converting to JPG:\nCommand \"%s\" failed!\n", command.c_str());
		return 3;
	}
	printDebug("%s.jpg was stored for viewing. \n", filename.c_str());

	//Delete temp file
	command = std::string("rm ") + tmpfile;
	system(command.c_str());
	return 0;
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

//image rotation by radian and rotation center
void Image::rotate(double radians, int offsetX, int offsetY) {
	vector<vector<unsigned char>> tempR;
	vector<vector<unsigned char>> tempG;
	vector<vector<unsigned char>> tempB;
	tempR.resize(h, vector<unsigned char>(w));
	tempG.resize(h, vector<unsigned char>(w));
	tempB.resize(h, vector<unsigned char>(w));

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

//TODO: Crop image by 2 set of coordinate
//TODO: Find the edge coordinate

//Print debug messages, if DEBUG flag is set
void printDebug(const char *format, ...) {
#ifdef DEBUG
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
#endif
}
