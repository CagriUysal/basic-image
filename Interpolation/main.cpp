#include "interp.h"

int main(int argc, char ** argv)
{	
	// read as BGR!
	Mat original = imread(argv[1]);
	
	Mat nearest;
	Mat bilinear;
    
    // scale the original image by factor 4 using 
    // nearest neighbor interpollation
	nearest = interpNN(original, 4);

    // scale the original image by same factor as NN 
    // for comparision, this time using bilinear interpollation
	bilinear = interpBilinear(original, 4);


	imwrite("original.jpg", original);
	imwrite("nearest.jpg", nearest);
	imwrite("bilinear.jpg", bilinear);
	
	waitKey(0);
} // main
