#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////     Importing Images	///////

void import_image() {

	string path = "Resources/test.jpg";

	//Matrix Data type to handle image

	Mat img = imread(path);	//Read the image from path
	
	imshow("Image", img);	//To show the image

	waitKey(0);		//To hold the image 
	//0 because for infinite time

}


////////		Importing Video		////////////

void import_video() {

	string path = "Resources/test_video.mp4";

	VideoCapture cap(path);  //For showing videocapture cap object
	Mat img;


	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(20);
	}

}

////////			webcam //////////////


void webcam() {

	//string path = "Resources/test_video.mp4";

	VideoCapture cap(0);  //0 for my laptop webcam  
	Mat img;


	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}

}

