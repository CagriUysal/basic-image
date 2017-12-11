#include "cagri_uysal_3.h"

int main(int argc,char** argv)
{
	// read as a grayscale image
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	Mat outImage;
	Mat cvDen;

	// denoise
	outImage = denoise(image, 24, 5);
	
	//fastNlMeansDenoising(image, cvDen);
	
	// save the denoised image
	imshow("original", image);
	imwrite("barbara24_denoised.png", outImage);
	//imshow("opencv", cvDen);
	waitKey(0);

	return 0;
}
