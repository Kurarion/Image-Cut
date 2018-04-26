#pragma once
#define WITH_RESIZE 1
#define WITHOUT_RESIZE 0

#pragma once
#include <iostream>
#include <cmath>
#include "highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "NotifyManager.h"
using namespace std;
using namespace cv;



class livewrite 
{
public:
	//livewrite(CRect &rect);
	static void init(/*CRect &rect,*/ NotifyManager* notify,Mat &img, int with_resize);
	static void cal_canny();
	static void reg_mouse();
	static void clear();
	static void close_window();
	//search point
	static bool start_search(int x, int y);
	static void search_point(int x, int y);
	static void remove_point();
	static void hand_draw(int x, int y);
	//draw line
	static void draw_line();
	//ouput
	static Mat preview();
	static bool output();
	static void gen_rgba(Mat img,Mat mask);

	//have Started?
	static bool start;

	//drawed point in vector 
	static vector<Point> drawed_points;

	//other vars
	static Mat img;
	static Mat img_back;
	static Mat img_rgba;
	static int last_x;
	static int last_y;
	static Scalar color_cir;
	static Scalar color_line;
	static Scalar color_line_dy;
	static String src;
	static Mat img_canny;
	static bool close;
	static bool with_hand;
	static bool with_hand_first;
	static bool real_preview;
	static NotifyManager* notifyManager;
	//static CRect rect;
};

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);