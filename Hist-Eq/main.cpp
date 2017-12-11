#include "hist_eq.h"

using namespace std;

int main(int argc, char** argv)
{
    
    Mat image;
    
    image = imread (argv[1], IMREAD_GRAYSCALE);
    
    imshow("original image", image);

    Mat eqImage;
	
    eqImage = histeq(image);
    	
    imshow("equalized Image", eqImage);
    
    // uncomment below if you want to save equlized image
    // imwrite("equalizedImage.png", eqImage);
    
    Mat openEq;
    
    // opencv histogram equalization function
    // for visual comparison
    equalizeHist(image, openEq);

    imshow("Opencv equalized", openEq);

    waitKey(0);

}
	

