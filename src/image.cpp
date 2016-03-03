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
//get image value by pixel
unsigned char Image::getR(int x, int y){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        return r[y][x];
    }
    return 0;
}
unsigned char Image::getG(int x, int y){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        return g[y][x];
    }
    return 0;
}

unsigned char Image::getB(int x, int y){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        return b[y][x];
    }
    return 0;
}

//set image value by pixel
void Image::setR(int x, int y, unsigned char value){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        r[y][x] = value;
    }else{
        //cout<<"pixel out of range\n";
    }
}
void Image::setG(int x, int y, unsigned char value){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        g[y][x] = value;
    }else{
        //cout<<"pixel out of range\n";
    }
}

void Image::setB(int x, int y, unsigned char value){
    if (this->w >x && this->h > y && x >=0 && y>= 0 ) {
        b[y][x] = value;
    }else{
        //cout<<"pixel out of range\n";
    }
}

//Save the image to a file
/*int Image::save(std::string filename) {
	FILE *file;
	std::string command;
	std::string tmpfile;
	tmpfile = filename;
	
	file = fopen(tmpfile.c_str(), "w");
	if(!file) {
		printDebug("\nCan't open file \"%s\" for writing!\n", filename.c_str());
		return 1;
        
      }
      }  */
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
//change the image color to black and white and remove some stain and winkle
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
//remove stain
void Image::StainRemoval()
{
int x, y;
double tmpA,tmpB,tmpC;

  for (y = 0; y < h; y++) {
        for (x = 0; x <w; x++) {

            
         /* cout<<(int)R[y][x];
          cout<<(int)G[y][x];  
          cout<<(int)B[y][x]<<endl;
          */ 

          if(r[y][x]>160&&(r[y][x]-b[y][x])>20&&(r[y][x]-g[y][x])>16){
          r[y][x]=255;
          g[y][x]=255;
          b[y][x]=255;
          }

          
          tmpA=(r[y][x]-g[y][x]);
          tmpB=(r[y][x]-b[y][x]);
          tmpC=(g[y][x]-b[y][x]);
          
          if( (abs(tmpA)>50)||(abs(tmpB)>50)||(abs(tmpC)>50) ){

          r[y][x]=255;
          g[y][x]=255;
          b[y][x]=255;
          }
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
void Image::crop(int startX, int startY, int endX, int endY){ 
/*
       int newW = endX - startX +1;        
       int newH = endY - startY +1;        
       int x, y;            
       for (y = HEIGHT-1; y>=0; y--) {        
       for (x = WIDTH-1; x>=0; x--) {            
       if (x>startX &&x < endX && y> startY && y< endY) {               
                
         }else{
            R[y].erase(R[y].begin()+x);               
           G[y].erase(G[y].begin()+x);                
           B[y].erase(B[y].begin()+x); 
         }                    
         }            
         }        
         this->WIDTH = newW;       
         this->HEIGHT = newH;  
   */
   
int newW = endX - startX +1;
    
    int newH = endY - startY +1;
    
    int x, y ,i, j;
    
    std::vector<std::vector<unsigned char> > tempR;
    std::vector<std::vector<unsigned char> > tempG;
    std::vector<std::vector<unsigned char> > tempB;
    tempR.resize(newH, std::vector<unsigned char>(newW));
    tempG.resize(newH, std::vector<unsigned char>(newW));
    tempB.resize(newH, std::vector<unsigned char>(newW));
    
    
    for (y = startY, j = 0; y< endY; y++,j++) {
        for (x = startX,i=0; x< endX; x++,i++) {
            
                tempR[j][i] = r[y][x];
                tempG[j][i] = g[y][x];
                tempB[j][i] = b[y][x];
            
        }
        
    }
    
    r.clear();
    g.clear();
    b.clear();
    r.resize(newH, std::vector<unsigned char>(newW));
    g.resize(newH, std::vector<unsigned char>(newW));
    b.resize(newH, std::vector<unsigned char>(newW));
    
    
    for (y = 0; y< newH; y++) {
        for (x = 0; x< newW; x++) {
            
            r[y][x] = tempR[y][x];
            g[y][x] = tempG[y][x];
            b[y][x] = tempB[y][x];
            
        }
        
    }
    
    this->w = newW;
    
    this->h = newH;
               
         }





//TODO: Find the edge coordinate



//Print debug messages, if DEBUG flag is set
void Image::printDebug(const char *format, ...) {
#ifdef DEBUG
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
#endif
}
