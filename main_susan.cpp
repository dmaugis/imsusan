#include <getopt.h>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
using namespace std;
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
/*
#include <cvm/cvm.h>
using namespace cvm;
*/
#include <susan.h>

static struct option long_options[] = {
	{"verbose",  		required_argument, 0, 'v'},
	{"help",     		no_argument,       0, 'h'},
	{"direction",     	no_argument,       0, 'd'},
	{"mask",     		required_argument, 0, 'm'},
	{"savgol",     		required_argument, 0, 's'},
	{0, 0, 0, 0}
};


inline std::string	mkname(const boost::filesystem::path& filename,const char* mid,const char* ext=".png",const char* sep="_")
{
	std::string base=std::string(filename.stem().c_str());
	if(mid && *mid)
		return base+std::string(sep)+std::string(mid)+std::string(ext);
	return base+std::string(ext);
}

int main(int argc, char** argv )
{
	int 	option_index = 0;
	int		bt=20;
	int		max_no_edges=2650;
	int		drawing_mode=0;
	while(1) {
		int c = getopt_long (argc, argv, "hds:m:v:",long_options, &option_index);
		if (c == -1)
			break;  // end of options
		switch (c) {
		case 'v':
			//verbose_level=atoi(optarg);
			break;
		case 'h':
			//usage(cerr,basename(argv[0]));
			//exit(1);
			break;		// never reached
		}
	}
	for(int i = optind; i < argc; i++) {
		boost::system::error_code c;
		boost::filesystem::path fullp(argv[i]);
		boost::filesystem::path p = basename(fullp);
		if(boost::filesystem::is_directory(fullp,c)) continue;

		Mat img = imread(argv[i], IMREAD_GRAYSCALE);
		if(img.empty()) {
			cerr << basename(argv[0]) << ": could not open file or invalid image file  '" << argv[i] << "'" << endl;
			continue;
		}
		img.convertTo(img,CV_8UC1);
		/*
		img=imreduce(img,420);
		imwritex(mkname(p.stem(),"",".jpg"),img);
		*/
		Mat		mid=susan::edge(img,8);
		imwrite(mkname(p,"E",".png"),mid);

		vector<Point2f>	corners=susan::corners(img,8);
		Mat M=img.clone();
		for( size_t i = 0; i < corners.size(); i++ ) {
					circle( M, corners[i], 5,  Scalar(0), 2, 8, 0 );
		}
		imwrite(mkname(p,"C",".png"),M);
	}
}
