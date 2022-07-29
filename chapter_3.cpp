#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>


using namespace std;
using namespace cv;


int main() {
	string path = "Resources/test.jpg";
	Mat img = imread(path);
	Mat imgResize;		//Object for resize an image
	Mat imgCrop;		//Object for cropping an image
	
	resize(img, imgResize, Size(),0.5,0.5); //Resize an Image   // It will half the image
															 //In size you can enter pixles

	Rect roi(200,200,200,200); //0,0 is from left upper most corner 500,300 pixles

	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Resized Image", imgResize);
	imshow("Cropped image", imgCrop);

	waitKey(0);

}