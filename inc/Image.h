/*********************************************************************/
/* Image.hpp: header file for image class                    		     */
/*                                                                   */
/*********************************************************************/
#ifndef IMAGE_HPP
#define IMAGE_HPP
#define SLEN    80		/* maximum length of file names */
#include <string>
#include <iostream>
#include <vector>
using std::vector;

class IMAGE{
public:
    int WIDTH;
    int HEIGHT;
    vector<vector<unsigned char> > R;
    vector<vector<unsigned char> > G;
    vector<vector<unsigned char> > B;
    
public:
    
    IMAGE();
    IMAGE(int w, int r);//construction declaration
    ~IMAGE();//destructor declaration
    
    int SaveImage(const char fname[SLEN]);
    void BlackNWhite();
    
    //image rotation by radian and rotation center
    void rotate(double radian, int offsetX, int offsetY);
    //crop image by 2 set of coordinate
    void cropIMG(int starX,int starY, int endX, int endY);
    //find the edge coordinate
    void findEdge(int edge[4]);
    
};

#endif
