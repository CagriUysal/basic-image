// Cagri UYSAL
// Hw #1

#include <opencv2/opencv.hpp>

using namespace cv;

Mat interpNN(const Mat &image, double scale);
Mat interpBilinear(const Mat &image, double scale);
uchar findIntensity (int row, int col, const Mat&image, double scale, int ch);

// Interpollation functions below works  for
// 3 channel BGR images !
// They can easly changed to work with grayscale images. 


// interpolation using nearest neighbor method
Mat interpNN(const Mat &image, double scale)
{	
	
	// scaled image
	Mat resizedImage(Size(round((double)image.cols * scale), 
				round((double)image.rows * scale)),image.type(), Scalar(0));

	for(int i = 0; i < image.channels(); i++)
		for(int row = 0 ; row < resizedImage.rows ; row++)
			for(int col = 0; col < resizedImage.cols; col++)
			{	
				// rounds the mapped fixel locations to
				// obtain nearest neigbor
				int inCol = round( (double) col / scale );
				int inRow = round( (double) row / scale );
				
				// checks out of boundries 
				if(inCol >= image.cols)
					inCol = image.cols - 1;
				if(inRow >= image.rows)
					inRow = image.rows - 1;
	
				resizedImage.at<Vec3b>(row, col)[i] = 
							image.at<Vec3b>(inRow, inCol)[i];
			}
			
	return resizedImage;
}
 
 

Mat interpBilinear(const Mat &image, double scale)
{

	Mat resizedImage(Size(round((double)image.cols * scale), 
				round((double)image.rows * scale)),image.type(), Scalar(0));
	
	// finds mapped pixel values for 3 channels
	// calls findIntensity function 
	for(int ch = 0; ch < image.channels(); ch++)	
		for(int row = 0 ; row < resizedImage.rows ; row++)
			for(int col = 0; col < resizedImage.cols; col++)
				resizedImage.at<Vec3b>(row, col)[ch] = findIntensity(row, col, image, scale, ch);
				
		return resizedImage;
}

// finds intensity value for corresponding pixel
// from given image
// uses bilinear interpolation

uchar findIntensity (int row, int col, const Mat&image, double scale ,int ch)
{	
	// inverse mapping
	double exactCol = (double) col / scale;
	double exactRow = (double) row / scale;
	
	// check out of boundries
	if(exactCol > image.cols - 1)
		exactCol = image.cols - 1;

	if(exactRow > image.rows - 1)
		exactRow = image.rows - 1;
	
	// check if exactCol and exactRow is integer
	// if it is, map exact location from input image
	if(floor(exactCol) == exactCol && 
		floor(exactRow) == exactRow)
			return image.at<Vec3b>(exactRow, exactCol)[ch];
	
	// check if exactCol is integer
	// if it is, only vertical interpolation is enough
	if( floor(exactCol) == exactCol ) 
	{
	int upperRow = floor(exactRow);
	int lowerRow = ceil(exactRow);

	uchar vertical  = image.at<Vec3b>(upperRow, int(exactCol))[ch] * (lowerRow - exactRow) 
		+ image.at<Vec3b>( lowerRow, int(exactCol) )[ch] * ( exactRow - upperRow);

	return vertical;
	}
	
	// check if exactRow is integer
	// if it is, only horizontal interpolation is enough
	if( floor(exactRow) == exactRow )
	{
	int leftCol = floor(exactCol);
	int rightCol = ceil(exactCol);

	uchar horizontal = image.at<Vec3b>(int(exactRow), leftCol)[ch] * (rightCol - exactCol) 
		+ image.at<Vec3b>( int(exactRow), rightCol )[ch] * ( exactCol - leftCol);

	return horizontal;
	}

	// Else, 4 neighbor interpolation is necessary

	// nearest upper left pixel
	int upperLeftCol = floor(exactCol);	
	int upperLeftRow = floor(exactRow);
	
	// nearest upper right pixel
	int upperRightCol = ceil(exactCol);
	int upperRightRow = floor(exactRow);
	
	// nearest lower left pixel
	int lowerLeftCol = floor(exactCol);
	int lowerLeftRow = ceil(exactRow);
	
	// nearest lower right pixel
	int lowerRightCol = ceil(exactCol);
	int lowerRightRow = ceil(exactRow);

	// upper horizontal interpolate
	uchar upperHor = image.at<Vec3b>(upperLeftRow, upperLeftCol)[ch] * (upperRightCol - exactCol) 
		+ image.at<Vec3b>(upperRightRow, upperRightCol)[ch] * ( exactCol - upperLeftCol);
	

	// lower horizontal interpolate
	uchar lowerHor = image.at<Vec3b>(lowerLeftRow, lowerLeftCol)[ch] * (lowerRightCol - exactCol) 
		+ image.at<Vec3b>(lowerRightRow, lowerRightCol)[ch] * ( exactCol - lowerLeftCol);

	
	// vertical interpolate
	// note that lowerLeftRow can be changed with lowerRightRow
	uchar vert = upperHor * (lowerLeftRow - exactRow) + lowerHor * (exactRow - upperLeftRow);
		
	return vert;
}


