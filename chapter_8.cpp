#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////    Face Detection	///////

//For face detection we will use viala jones method haarcascade
//We already have model trained for it

int main() {

	string path = "Resources/test.jpg";
	Mat img = imread(path);	//Read the image from path

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	if (faceCascade.empty())
		cout << "XML file not loaded" << endl;

	//To detect the faces and store them we need bounding boxes
	//bounding boxes basically are rectangles which are vector

	vector<Rect> faces;		//Vector of rectangles(Faces)

	faceCascade.detectMultiScale(img, faces,1.1,10);

	system("clear");
	cout << faces.size() << endl;
	cout << faces[0].tl() << " " << faces[0].br() << endl;

	for (int i = 0; i < faces.size(); i++) {

		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("Image", img);	//To show the image
	waitKey(0);		//To hold the image 
	//0 because for infinite time

}
