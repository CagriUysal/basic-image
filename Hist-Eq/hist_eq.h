//Cagri UYSAL 
// HW #2 

#include "opencv2/opencv.hpp"
using namespace cv;

#define INTENSITY_RANGE 256

// this function operates on grayscale images
Mat histeq(Mat image)
{
	Mat outImage(image.size(), image.type(), Scalar(0));
	
    // stores the number of intensity values in the image
    // i.e. histogram
    unsigned int hist [INTENSITY_RANGE] = {0} ;
                
    // finds the total number of pixels
    unsigned int totalPixel = image.rows * image.cols;

	//store the histogram values
	for(int row = 0; row < image.rows; row++)
		for(int col = 0; col < image.cols; col++)
		    hist[image.at<uchar>(row, col)]++;
    
    double prob [INTENSITY_RANGE] ;

	// calculate probabilities by dividing each
	// histogram value to total number of pixels
	for(int i = 0; i < INTENSITY_RANGE; i++)
		prob[i] = (double) hist[i] / totalPixel;
	
    
    // output of histogram equalization
    double s [INTENSITY_RANGE] = {0};
    
    // Use histogram equalization transfer function
    // i.e. cummulative probability
    for(int i =0; i < INTENSITY_RANGE; i++)
        for(int j = 0; j <= i; j++)
            s[i] += prob[j] * (INTENSITY_RANGE - 1);

    
    // round fractions to nearest integer 
    unsigned int roundedS[INTENSITY_RANGE];

    for(int i = 0; i < INTENSITY_RANGE ; i++)
        roundedS[i] =  round(s[i]);
    
    // obtain output image by histogram equalization
    for(int row = 0; row < outImage.rows; row++)
        for(int col = 0; col < outImage.cols; col++ )
            outImage.at<uchar>(row, col) = 
              roundedS[image.at<uchar>(row, col)];
        
    return outImage;
}

