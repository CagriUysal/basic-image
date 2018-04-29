// Cagri UYSAL
// HW #3

#include "opencv2/opencv.hpp"
#include <math.h>
using namespace cv;

// this function operates on grayscale images.
// its inputs are a noisy image, standard deviation of the noise and the window size.
// stddev is the square root of variance.
// windowSize is the neighborhood you are going to apply your filter.
// windowSize of 5 means that you are going to work with 5x5 sized windows.
// it returns the denoised image.
// the output image has the same size as the input image.
Mat denoise(Mat image, double noiseStdDev, int windowSize)
{
	Mat outImage(image.size(), CV_8UC1);

	double noiseVar = pow(noiseStdDev, 2);// variance of noise
	double localMean; // mean of sub-image
	double localVar;  // variance of sub-image
	double total;

	for(int row = 0; row < image.rows; row++)
		for(int col = 0; col < image.cols; col++ )
		{	
				
			// calculate local mean of sub image
			total = 0; 
			for(int subRow =  row - windowSize / 2 ;
				subRow <= row + windowSize / 2; subRow++)
				for(int subCol = col - windowSize / 2; 
					subCol <= col + windowSize / 2; subCol++ )
				{	
					// padding with zero if out of range
					if(subRow < 0 || subRow >= outImage.rows ||
						subCol < 0 || subCol >= outImage.cols)
					  	total += 0;
					else 
						total += image.at<uchar>(subRow,subCol);	
				}
					
			localMean = total / pow(windowSize, 2);
			
			
			// calculate local variance of sub image
			total = 0;
			for(int subRow =  row - windowSize / 2 ;
				subRow <= row + windowSize / 2; subRow++)
				for(int subCol = col - windowSize / 2; 
					subCol <= col + windowSize / 2; subCol++ )
				{	
					// padding with zero if out of range
					if(subRow < 0 || subRow >= outImage.rows ||
						subCol < 0 || subCol >= outImage.cols)
					  	total += pow(localMean,2);
					else{
						uchar pixVal = image.at<uchar>(subRow,subCol);
						total += pow((pixVal - localMean), 2);
					}
				}
			
			localVar = total / pow(windowSize, 2);

			int result = image.at<uchar>(row, col)
			- round( (noiseVar / localVar) * 
			 (image.at<uchar>(row,col) - localMean));
			
			// check out of ranges
			// map negative values to 0
			// values greater than 255 to 255.
			if (result < 0)
				result = 0;
			else if (result > 255)
				result = 255;

			outImage.at<uchar>(row, col) = result;

		} // end for

	return outImage;
}
