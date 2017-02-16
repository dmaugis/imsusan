#include <getopt.h>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;
#include <cvm/cvm.h>
using namespace cvm;
#include <susan.h>




extern "C" {

#define MAX_CORNERS   15000  /* max corners per frame */
	typedef  struct {
		int x,y,info, dx, dy, I;
	} CORNER_LIST[MAX_CORNERS];

	void setup_brightness_lut(uchar **bp,int thresh,int form);
	void susan_smoothing(int three_by_three,uchar* in,float dt,int x_size,int y_size,uchar* bp);
	void susan_edges_small(uchar* in,int* r,uchar* mid,uchar* bp,int max_no,int x_size,int y_size);
	void	susan_edges(uchar* in,int* r,uchar* mid,uchar* bp,int max_no,int x_size,int y_size);
	void	susan_thin(int* r,uchar* mid,int x_size,int y_size);
	void	edge_draw(uchar* in,uchar* mid,int x_size,int y_size,int drawing_mode);

	void	susan_corners(uchar *in,int* r,uchar *bp,int max_no,CORNER_LIST corner_list,int x_size,int y_size);
	void	corner_draw(uchar *in,CORNER_LIST corner_list,int x_size,int drawing_mode);
};



namespace susan
{

Mat		edge(Mat	img,int	bt,bool	thin,int	max_no_edges)  /* brightness threshold */
{
	int		x_size=img.cols;
	int		y_size=img.rows;
	uchar  *in=img.data;

	Mat		r(img.size(),CV_32SC1,Scalar(0));

	uchar *bp=NULL;
	setup_brightness_lut(&bp,bt,6);

	Mat		mid(img.size(),CV_8UC1,Scalar(100));

	susan_edges(in,(int*)r.data,mid.data,bp,max_no_edges,x_size,y_size);
	if(thin)
		susan_thin((int*)r.data,mid.data,x_size,y_size);
	//edge_draw(in,mid.data,x_size,y_size,drawing_mode);
	return mid<10;
}

vector<Point2f>	corners(Mat img,int	bt)
{
	int        max_no_corners=15000-2;
	CORNER_LIST corner_list;
	int		x_size=img.cols;
	int		y_size=img.rows;
	uchar  *in=img.data;

	Mat		r(img.size(),CV_32SC1,Scalar(0));
	uchar *bp=NULL;
	setup_brightness_lut(&bp,bt,6);
	susan_corners(in,(int*)r.data,bp,max_no_corners,corner_list,x_size,y_size);
	int   n=0;
	vector<Point2f>	points;
	while(corner_list[n].info != 7) {
		points.push_back(Point2f(corner_list[n].x,corner_list[n].y));
		n++;
	}
	return points;
}

};

