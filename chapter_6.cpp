#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////     Color detection	///////

int main() { 

	string path = "Resources/shapes.png";

	Mat img = imread(path);	//Read the image from path
	Mat imgHSV;  //H = Hue // s = Saturaion // V = Value 
				 //Converting image to HSV beccause it is easy to detect color in HSV mode
	Mat mask;	//Output masked image or detected image

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	cvtColor(img, imgHSV, COLOR_BGR2HSV); //Converting normal to HSV image

	namedWindow("Trackbars", (640,200));  //Creating Trackbar which will allow us to change HSV values in real time
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("sat Min", "Trackbars", &smin, 255);
	createTrackbar("sat Max", "Trackbars", &smax, 255);
	createTrackbar("vmin Min", "Trackbars", &vmin, 255);
	createTrackbar("vmax Max", "Trackbars", &vmax, 255);

	//So we can find min and max values
	//After getting min and max you can change the values
	while (true) {

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);



		//Will detect all the values or color which lies between upper and lower
		inRange(imgHSV, lower, upper, mask); //Input, lower range, Upper range, Masked Output




		imshow("Image", img);	//To show the image
		imshow("Hsv Image", imgHSV);
		imshow("Masked image", mask);
		waitKey(1);		//To hold the image 
		//0 because for infinite time
	}
	return 0;
}