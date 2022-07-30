#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////     Shape/Contour Detection	///////

void getContours(Mat imgDil, Mat img) {
	
	vector<vector<Point>> contours; //Will be points of each shape or contours
	vector<Vec4i> hierarchy;
	
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255,0,255),10);
	
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	string objectType;
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);

		cout << area << endl;
		if (area > 1000) {					//Removing noise //Only selecting which shape has area greater than 1000

			float peri = arcLength(contours[i],true); //true for whether it is close area
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);  //Can write -1 instead of i to draw on each shape 
							//If you write contour instead of conPoly then it wiil draw whole shape instead of shape on shape
			cout << conPoly[i].size() << endl;	//counting the points
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(),Scalar(0,255,0),5);	//Draw Green Rectangle shapes on founded contour
			
			int objCorner = (int)conPoly[i].size(); //Coners of each shapes
			if (objCorner == 3)
				objectType = "Tri";
			else if (objCorner == 4) {
				float aspRatio = (float)boundRect[i].width/(float)boundRect[i].height;
				cout << "AspRatio " << aspRatio << endl;
				if (aspRatio > 0.9 && aspRatio < 1.1)
					objectType = "Square";
				else
					objectType = "Rect";
			}
			else
				objectType = "Circle";
			putText(img, objectType, {boundRect[i].x,boundRect[i].y}, FONT_HERSHEY_PLAIN, 1.4, Scalar(0, 0, 0), 2); //Printing on shapes
		}
	}
}

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);	//Read the image from path
	Mat imgGray;
	Mat imgBlur, imgCanny, imgDil, imgErode;


	//Preprocessing of the image
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel); //We are using dilation image because there will be gape in canny edge detected 
										// which we can fill by increasing the thickness of borders so using dilated

	system("clear");
	getContours(imgDil, img);

	
	imshow("Image", img);	//To show the image
	//imshow("imgBlur", imgBlur);
	//imshow("imgGray", imgGray);
	//imshow("imgCanny", imgCanny);
	//imshow("Image Dil", imgDil);
	//imshow("Image Erode", imgErode);
	waitKey(0);		

}
