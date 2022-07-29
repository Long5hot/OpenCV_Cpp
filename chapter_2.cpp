#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////    Basics Function	///////

void main() {

	string path = "Resources/test.jpg";

	//Matrix Data type to handle image

	Mat img = imread(path);	//Read the image from path
	Mat imgGray;					//My Grayscale image object	
	Mat imgBlur;					//Img blur object
	Mat imgCanny;					// to show edge detected object
	Mat imgDil;						//Dilated image
	Mat imgErode;					//Erolded image


	cvtColor(img,imgGray,COLOR_BGR2GRAY);  //input image, Output image , filter

	GaussianBlur(img, imgBlur, Size(7,7),5,0); //(7,7) and 5 show how much blur you want

	//Canny Edge detector
	Canny(imgBlur, imgCanny, 25, 75);	//Threshold_1 and Threshold_2 are the values for edge detection 
																	// Lesser the value more the edges in picture

	//dialate the image :: Increase the thickness of image
	//Erold the image	:: Decrease the thickness of image

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3)); //This creates kernel which we can use for dilation
																		 //Increase the size will dilate more and erode more

	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

	//imshow("Image", img);	//To show the input image
	//imshow("Image Gray", imgGray); //To show output image
	//imshow("Gausian Blur", imgBlur); //To show Blur image
	imshow("Edge Detected", imgCanny); //To show Edge detected object
	imshow("Image Dilation", imgDil);		//Dilated image with thick edges
	imshow("Image Erode", imgErode);		//Eroded Image with thin edges
	waitKey(0);		//To hold the image //0 because for infinite time
	
}
