
#include "livewrite.h"

//��ʼ����̬����
bool livewrite::start = false;
vector<Point> livewrite::drawed_points{ Point(0,0) };
Mat livewrite::img = Mat();
Mat livewrite::img_back = Mat();
Mat livewrite::img_rgba = Mat();
int livewrite::last_x = 0;
int livewrite::last_y = 0;
Scalar livewrite::color_cir = Scalar(229, 112, 4);
Scalar livewrite::color_line = Scalar(31, 161, 33);
Scalar livewrite::color_line_dy = Scalar(4, 22, 168);
Mat livewrite::img_canny = Mat();
//CRect livewrite::rect = CRect();
String livewrite::src = String();
bool livewrite::close=false;
bool livewrite::with_hand = false;
bool livewrite::with_hand_first = true;
bool livewrite::real_preview = false;
NotifyManager* livewrite::notifyManager = new NotifyManager();
//��ʼ��
void livewrite::init(/*CRect &rect, */NotifyManager* notify,Mat &img, int with_resize)
{
	
	//livewrite::rect = rect;
	livewrite::notifyManager = notify;
	livewrite::img = img;
	livewrite::img_back = livewrite::img.clone();
	livewrite::close = false;
	livewrite::with_hand_first = true;
	//livewrite::real_preview = false;
	src = "���ܼ���[����м����¹ر�]";
	// The values in cost matrix ranges from 0~1
	drawed_points.clear();
	if (with_resize == WITH_RESIZE) {
		//resize(livewrite::img, livewrite::img, Size(livewrite::rect.Width(), livewrite::rect.Height()));
		//resize(livewrite::img_back, livewrite::img_back, Size(livewrite::rect.Width(), livewrite::rect.Height()));
		src = "src1";
	}
	//��������⣺ʹ��CV_WINDOW_NORMALʱ��Ȼ�ܵ���size�����ǻ�Ĭ���ϴδ��ڴ�С
	//�������������ʹ��CV_WINDOW_AUTOSIZE,����img��С��window������CV_WINDOW_NORMAL

		namedWindow(src, CV_WINDOW_AUTOSIZE);

		cv::imshow(src, livewrite::img);

		destroyWindow(src);
		namedWindow(src, CV_WINDOW_NORMAL);

		cv::imshow(src, livewrite::img);



	
	cal_canny();
	//reg_mouse();
}
//ʹ��canny�㷨
void livewrite::cal_canny()
{

	Canny(img, img_canny, 85, 170);
	cv::imwrite("output/img_canny.png", img_canny);


}
//ע�����ص���������ʱˢ��
void livewrite::reg_mouse()
{
	//�������ص�����
	setMouseCallback(src, on_mouse, &img);
	int key;
	//����loop-ˢ��ͼƬ
	while (!close)
	{
		cv::imshow(src, img);
		key=cvWaitKey(40);
		switch (key)
		{
		case 'z':
			with_hand = false;
			//�����ź�
			notifyManager->notifyHandChanged();
			break;
		case 'x':
			with_hand = true;
			//�����ź�
			notifyManager->notifyHandChanged();
			break;
		case 'q':
			close_window();
			break;
		}

	}
}
//������ͼƬ��ص���������
void livewrite::clear()
{
	drawed_points.clear();
	img =  Mat();
	last_x = 0;
	last_y = 0;
	img_canny = Mat();
	img_rgba = Mat();
	close = true;
	cv::destroyWindow("���ܼ���[����м����¹ر�]");
	//rect = CRect();
}
void livewrite::close_window()
{
	close = true;
	cv::destroyWindow("���ܼ���[����м����¹ر�]");
}
//�����Ƿ�ʼ������һ���㣬����򵥵��þ���ֵ�����ж�
bool livewrite::start_search(int x, int y)
{
	int dis = abs(x - last_x) + abs(y - last_y);
	if (dis < 27)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//���ݵ�ǰ������꿪ʼ������һ���ָ��
void livewrite::search_point(int x, int y)
{
	int xx, yy;
	int may_x, may_y;
	Point last_last_point = drawed_points.back();
	Point current_point(x, y);

	//test
	//xx = x;
	//yy = y;
	//�����һ���㲻��Canny�еķָ����е�һ��
	if (img_canny.at<uchar>(Point(last_x, last_y)) != 255)
	{
		//�Ե�ǰ�������ﵽ�������Χ������������cannyͼ������Ϊ255���������Ϊ��һ���ָ��
		//�����ж��Ƿ�ֱ���Ƿָ��
		if (img_canny.at<uchar>(current_point) != 255)
		{
			for (int k = 1; k < 6; ++k)
			{
				for (int i = -k; i <= k; ++i)//����
				{
					for (int j = -k; j <= k; ++j)//����
					{
						//����Ƿ�����������
						if (abs(i) != k&&abs(j) != k)
							continue;
						yy = y + i;
						xx = x + j;
						//�ж��Ƿ�Խ��
						if (xx < 0 || yy < 0)
							continue;
						if (xx >= img.cols || yy >= img.rows)
							continue;
						if (img_canny.at<uchar>(Point(xx, yy)) == 255)
						{
							//set last_
							drawed_points.push_back(Point(xx, yy));
							last_x = xx;
							last_y = yy;

							//draw_line();
							circle(img, Point(xx, yy), 1, color_cir, 3);
							line(img, last_last_point, Point(xx, yy), color_line, 2);

							if (real_preview) {

								//�����ź�
								notifyManager->notifyPreviewChanged();
							}
							return;
						}
					}
				}
			}
		}
		else
		{
			xx = x;
			yy = y;

			//set last_
			drawed_points.push_back(Point(xx, yy));
			last_x = xx;
			last_y = yy;

			//draw_line();
			circle(img, Point(xx, yy), 1, color_cir, 3);
			line(img, last_last_point, Point(xx, yy), color_line, 2);
			if (real_preview) {

				//�����ź�
				notifyManager->notifyPreviewChanged();
			}
			return;
		}
	}
	//����Ƿָ��ߵ�һ�㣬�����ŷָ�����
	else
	{
		//kȦ����
		//int k = 3;
		int min_dis = 40;
		int current_min_dis = (x - last_x)*(x - last_x) + (y - last_y)*(y - last_y);
		int dis;
		bool need_draw = false;
		int min_x, max_x;
		int min_y, max_y;

		//img_canny.at<uchar>(Point(last_x, last_y)) == 255;
		for (int k = 1; k < 10; ++k)
		{
			for (int i = -k; i <= k; ++i)//����
			{
				for (int j = -k; j <= k; ++j)//����
				{
					//����Ƿ�����������
					if (abs(i) != k&&abs(j) != k)
						continue;
					may_y = last_y + i;
					may_x = last_x + j;
					//�ж��Ƿ�Խ��
					if (may_x < 0 || may_y < 0)
						continue;
					if (may_x >= img.cols || may_y >= img.rows)
						continue;
					//�ж������ĵ��Ƿ��ǲ������ģ�����
					min_x = (last_x < may_x) ? last_x : may_x;
					max_x = (last_x >= may_x) ? last_x : may_x;
					min_y = (last_y < may_y) ? last_y : may_y;
					max_y = (last_y >= may_y) ? last_y : may_y;
					int time = 2;
					int min_time = max(max_y - min_y, max_x - max_y);
					if (max_x - min_x > 2 && max_y - min_y > 2) {
						for (int m = min_x + 1; m < max_x; ++m)
						{
							for (int n = min_y + 1; n < max_y; ++n)
							{
								if (img_canny.at<uchar>(Point(m, n)) == 255)
									time++;
							}
						}
						if (time < min_time)
							continue;
					}

					//������С������
					dis = (x - may_x)*(x - may_x) + (y - may_y)*(y - may_y);
					if (dis < min_dis)
						return;

					if (img_canny.at<uchar>(Point(may_x, may_y)) == 255 && dis < current_min_dis)
					{
						need_draw = true;
						xx = may_x;
						yy = may_y;
						current_min_dis = dis;
					}
				}
			}


		}
		if (need_draw) {
			//set last_
			drawed_points.push_back(Point(xx, yy));
			last_x = xx;
			last_y = yy;

			//draw_line();
			circle(img, Point(xx, yy), 1, color_cir, 3);
			line(img, last_last_point, Point(xx, yy), color_line, 2);

			if (real_preview) {

				//�����ź�
				notifyManager->notifyPreviewChanged();
			}
			return;
		}

	}


}
//ɾ�����һ��vector�ķָ��
void livewrite::remove_point()
{
	if ((int)drawed_points.size() > 0) {
		drawed_points.erase(drawed_points.end() - 1);
		last_x = (*(drawed_points.end() - 1)).x;
		last_y = (*(drawed_points.end() - 1)).y;
	}
		
	img = img_back.clone();

	draw_line();
	if (real_preview) {

		//�����ź�
		notifyManager->notifyPreviewChanged();
	}
}
void livewrite::hand_draw(int x, int y)
{
	//set last_
	drawed_points.push_back(Point(x, y));


	//draw_line();
	circle(img, Point(x, y), 1, color_cir, 3);
	line(img, Point(last_x,last_y), Point(x, y), color_line, 2);
	//set last
	last_x = x;
	last_y = y;

	if (real_preview) {

		//�����ź�
		notifyManager->notifyPreviewChanged();
	}


}
//����vector�������
void livewrite::draw_line()
{
	vector<Point>::iterator it;

	int i = 0;
	int end = drawed_points.size();

	//log
	//freopen("points_num.txt", "w", stdout);
	//cout <<"num:"<<end<<endl<<endl;
	//freopen("CON", "w", stdout);

	if (end > 1) {
		it = drawed_points.begin();
		circle(img, *it, 2, color_cir, 3);
		for (; i < end - 1; ++it, ++i) {


			line(img, *it, *(it + 1), color_line, 2);
			circle(img, *(it + 1), 1, color_cir, 3);
			//String x = "it: x:" + (*it).x + " y : " +(*it).y+ "\nnext: x:"+next.x+ " y : "+next.y;
			//freopen("log.txt", "w", stdout);
			//cout << "ok" << endl;
			//cout << "it: x:" + (*it).x << " y : " + (*it).y << "next: x:" + next.x << " y : " + next.y;
			//cout << endl;
			//freopen("CON", "w", stdout); //recover stdout(Windows) 

		}
	}


}
//Ԥ���ָ�ͼ
Mat livewrite::preview()
{
	if ((int)drawed_points.size()>3)
	{
		//ʹ��floodFill���mask
		Mat mask = Mat::zeros(img.size(), CV_8UC1);
		//����vector��mask
		vector<Point>::iterator it;
		int max_x = 0;
		int min_x = img.cols;
		int max_y = 0;
		int min_y = img.rows;

		int i = 0;
		int end = drawed_points.size();

		if (end > 1) {
			it = drawed_points.begin();
			//circle(mask, *it, 2, color_cir, 3);
			for (; i < end - 1; ++it, ++i) {

				if ((*it).x < min_x)
					min_x = (*it).x;
				if ((*it).y < min_y)
					min_y = (*it).y;
				if ((*it).x > max_x)
					max_x = (*it).x;
				if ((*it).y > max_y)
					max_y = (*it).y;

				line(mask, *it, *(it + 1), Scalar(255), 1);
				//circle(mask, *(it + 1), 1, color_cir, 3);

			}
		}
		//��β����
		line(mask, drawed_points.front(), drawed_points.back(), Scalar(255), 1);
		//ȷ���ڵ�
		Point seed;
		seed.x = (max_x + min_x) / 2;
		seed.y = (max_y + min_y) / 2;
		//floodFill
		cv::floodFill(mask, seed, 255, NULL, cvScalarAll(0), cvScalarAll(0), CV_FLOODFILL_FIXED_RANGE);

		Mat maskImg;

		img_back.copyTo(maskImg, mask);
		//imwrite("mask.png", mask);
		//imshow("���ղü�ͼ", maskImg);
		//imwrite("final_output.png", maskImg);

		return maskImg;
	}
	else
	{
		return Mat();
	}

}
//���Ȧѡ��ͼƬ
bool livewrite::output()
{
	if ((int)drawed_points.size()>3)
	{
		//ʹ��floodFill���mask
		Mat mask = Mat::zeros(img.size(), CV_8UC1);
		//����vector��mask
		vector<Point>::iterator it;
		int max_x = 0;
		int min_x = img.cols;
		int max_y = 0;
		int min_y = img.rows;

		int i = 0;
		int end = drawed_points.size();

		if (end > 1) {
			it = drawed_points.begin();
			//circle(mask, *it, 2, color_cir, 3);
			for (; i < end - 1; ++it, ++i) {

				if ((*it).x < min_x)
					min_x = (*it).x;
				if ((*it).y < min_y)
					min_y = (*it).y;
				if ((*it).x > max_x)
					max_x = (*it).x;
				if ((*it).y > max_y)
					max_y = (*it).y;

				line(mask, *it, *(it + 1), Scalar(255), 1);
				//circle(mask, *(it + 1), 1, color_cir, 3);

			}
		}
		//��β����
		line(mask, drawed_points.front(), drawed_points.back(), Scalar(255), 1);
		//ȷ���ڵ�
		Point seed;
		seed.x = (max_x + min_x) / 2;
		seed.y = (max_y + min_y) / 2;
		//floodFill
		cv::floodFill(mask, seed, 255, NULL, cvScalarAll(0), cvScalarAll(0), FLOODFILL_FIXED_RANGE);
		//mask = imread("mask_.png",-1);
		//imwrite("mask1.png", mask);
		//imshow("xxx", mask);
		Mat maskImg;
		close = true;
		cv::imwrite("output/origin.png", img_back);
		cv::imwrite("output/example_ouput.png", img);
		img_back.copyTo(maskImg, mask);
		cv::imwrite("output/mask.png", mask);
		cv::imshow("���ܼ���[����м����¹ر�]", maskImg);
		cv::imwrite("output/final_output.png", maskImg);
		gen_rgba(maskImg,mask);
		cv::imwrite("output/final_output_rgba.png", img_rgba);

		return true;
	}
	else
	{
		return false;
	}
}
//����һ��͸���ķָ�ͼ
void livewrite::gen_rgba(Mat img, Mat mask)
{
	img_rgba = Mat::zeros(img.size(), CV_8UC4);
	for (int i = 0; i < img_rgba.rows; ++i) {
		for (int j = 0; j < img_rgba.cols; ++j) {
			if (mask.at<uchar>(Point(j, i)) == 255)
			{
				Vec4b& rgba = img_rgba.at<Vec4b>(Point(j, i));
				Vec3b& rgb = img.at<Vec3b>(Point(j, i));
				rgba[0] = rgb[0];
				rgba[1] = rgb[1];
				rgba[2] = rgb[2];
				rgba[3] = 255;

			}
		}
	}
}
//���̻ص�����

//���ص�����
void on_mouse(int EVENT, int x, int y, int flags, void * userdata)
{
	Mat hh;
	hh = *(Mat*)userdata;
	Point p(x, y);
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN:
	{

		//printf("b=%d\t", hh.at<Vec3b>(p)[0]);
		//printf("g=%d\t", hh.at<Vec3b>(p)[1]);
		//printf("r=%d\n", hh.at<Vec3b>(p)[2]);
		//circle(hh, p, 2, Scalar(255), 3);

		if (!livewrite::with_hand) {
			if (!livewrite::start)
			{
				//livewrite::cal_canny();
				//circle(hh, p, 1, Scalar(202,62,63), 3);
				livewrite::drawed_points.push_back(Point(x, y));
				livewrite::last_x = x;
				livewrite::last_y = y;
				circle(livewrite::img, Point(x, y), 2, livewrite::color_cir, 3);
				//livewrite::search_point(x, y);
				livewrite::with_hand_first = false;
			}
			livewrite::start = !livewrite::start;
			if (!livewrite::start)
			{
				cv::imwrite("output/example_ouput.png", livewrite::img);
			}
		}
		else {
			if (livewrite::with_hand_first) {
				livewrite::drawed_points.push_back(Point(x, y));
				livewrite::last_x = x;
				livewrite::last_y = y;
				circle(livewrite::img, Point(x, y), 2, livewrite::color_cir, 3);
				livewrite::with_hand_first = false;
			}
			else {
				livewrite::hand_draw(x,y);
			}

		}
	}
	break;
	case EVENT_RBUTTONDOWN:
	{
		//livewrite::draw_line();
		//ɾ�����һ����
		livewrite::remove_point();

	}
	break;
	case EVENT_MOUSEMOVE:
	{
		if (!livewrite::with_hand) {
			if (livewrite::start)
			{
				//line(livewrite::img, Point(x,y), Point(livewrite::last_x, livewrite::last_y), livewrite::color_line_dy, 2);	
				if (livewrite::start_search(x, y))
					livewrite::search_point(x, y);
			}
		}
	}
	break;
	case EVENT_MBUTTONDOWN:
	{
		livewrite::clear();
	}

	}
}


