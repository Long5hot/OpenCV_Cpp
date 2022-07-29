#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>


using namespace std;
using namespace cv;

///					Draw SHapes and Text

int main() {

	//Blank Image
	Mat img(512,512,CV_8UC3,Scalar(255,255,255));  
													//CV_8UC3 : 2^8-->(0-255) Thats why (U:unsigned) and 3:BGR
												  //(BGR) : for Blue Image (255,0,0)
												//For Black(0,0,0)
												//For Purple : (255,0,255)  WHite : (255,255,255)

	//circle(img, Point(256, 256), 155, Scalar(0, 69, 255), 10);
	circle(img, Point(256,256), 155, Scalar(0, 69, 255),FILLED);  //Making circle at center thats why 256 256 
																			//0,69,255 for orange 
	
																	//10 for thickness or MACRO FILLED
	
	//rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), 3);
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
						//First point is for upper left corner of rectangle
						//Second point is for lower right corner of rectangle


	line(img, Point(130, 296), Point(382, 296), Scalar(0, 0, 0), 4);
	//First point is for first point of line
	//Second point is for second point of line		//For this case its horizontal line
	
	putText(img, "My lesson", Point(130, 262), FONT_HERSHEY_DUPLEX,1.5,Scalar(0,0,0),4);
									//This Point Shows from where my lower left text will start from
									//FONT_HERSHEY_DUPLEX is font style
									//1.5 is fontsize  //4 is thickness
	imshow("Blue Image", img);
	waitKey(0);
}