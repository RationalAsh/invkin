#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

#define CAMERA 0
#define VWIDTH 640
#define VHEIGHT 480
#define HORIZ 1
#define RADIUS 10

using namespace cv;
using namespace std;

Scalar linecolor = Scalar(0,255,0);
Scalar rectcolor = Scalar(0,200,0);


//Function to find the centroid of a binary image
void getCentroid(Mat &thresholded_image, Point &Centroid, int &Area)
{
    ///The object that holds all the centroids.
    ///Pass in the image. The boolean true tells the function that 
    ///the image is binary
    Moments m = moments(thresholded_image, true);
    ///Moment along x axis
    double M10 = m.m10;
    ///Moment along y-axis;
    double M01 = m.m01;
    ///Area
    double M00 = m.m00;
    Centroid.x  = int(M10/M00);
    Centroid.y  = int(M01/M00);
    Area        = int(M00);
}

int main(int argc, char** argv)
{
    Mat frame, head, tail;
    char keypress;

    int rlower_h = 0;   int glower_h = 0;   int blower_h = 0;
    int rupper_h = 255; int gupper_h = 255; int bupper_h = 255;
    
    int rlower_t = 0;   int glower_t = 0;   int blower_t = 0;
    int rupper_t = 255; int gupper_t = 255; int bupper_t = 255;

    int max_thresh = 255;

    Scalar head_lower, head_upper,
	tail_lower, tail_upper;
    Point head_centroid, tail_centroid, direction;
    Point head_prev(0,0); Point motion(0,0);
    int head_area, tail_area;

    namedWindow("head");
    namedWindow("tail");
    createTrackbar("R Upper", "head", &rupper_h, max_thresh, NULL);
    createTrackbar("R Lower", "head", &rlower_h, max_thresh, NULL);
    createTrackbar("G Upper", "head", &gupper_h, max_thresh, NULL);
    createTrackbar("G Lower", "head", &glower_h, max_thresh, NULL);
    createTrackbar("B Upper", "head", &bupper_h, max_thresh, NULL);
    createTrackbar("B Lower", "head", &blower_h, max_thresh, NULL);

    createTrackbar("R Upper", "tail", &rupper_t, max_thresh, NULL);
    createTrackbar("R Lower", "tail", &rlower_t, max_thresh, NULL);
    createTrackbar("G Upper", "tail", &gupper_t, max_thresh, NULL);
    createTrackbar("G Lower", "tail", &glower_t, max_thresh, NULL);
    createTrackbar("B Upper", "tail", &bupper_t, max_thresh, NULL);
    createTrackbar("B Lower", "tail", &blower_t, max_thresh, NULL);

    VideoCapture camera;

    camera.open(CAMERA);
    //Setting the camera resolution
    camera.set(CV_CAP_PROP_FRAME_WIDTH, VWIDTH);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, VHEIGHT);

    while(1)
    {
	//Get frame from camera
	camera >> frame;
	flip(frame, frame, HORIZ);
        //Threshold out the green marker(tail)
	//Threshold out the red marker(head)
	inRange(frame, Scalar(rlower_h, glower_h, blower_h),
		Scalar(rupper_h, gupper_h, bupper_h), head);
	inRange(frame, Scalar(rlower_t, glower_t, blower_t),
		Scalar(rupper_t, gupper_t, bupper_t), tail);
	medianBlur(head, head, 7);
             
	//Get coordinates of the tail marker
	getCentroid(tail, tail_centroid, tail_area);
	//Get coordinates of the head marker
	getCentroid(head, head_centroid, head_area);
	//Subtract the coordinates to get a direction vector
	direction = head_centroid - tail_centroid;

	//Draw the appropriate stuff on the image
	motion = head_centroid - head_prev;
	line(frame, tail_centroid, head_centroid, linecolor);
	circle(frame, head_centroid, RADIUS, linecolor);
	
	//cout<<"Direction: "<<direction<<endl;
	//Use the direction vector to decide which way the arm must move
	//Display the motion as output on the terminal
	imshow("head", head);
	imshow("tail", tail);
	imshow("frame", frame);
	
	head_prev = head_centroid;
	
	keypress = waitKey(10);
	if(keypress == 27) break;
	if(keypress == 's')
	{
	    //save thresholds
	    
	    //Show directions
	    cout<<"Direction is: "<<direction<<endl;
	    break;
	}
	
	
	//Use the sliders to adjust the thresholds
	//Save the thresholds in variables
	//break out of loop
    }

    
    return 0;

}
