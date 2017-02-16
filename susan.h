#ifndef __SUSAN_H
#define __SUSAN_H

namespace susan
{

Mat						edge(Mat	img,int	bt=20,bool	thin=true,int	max_no_edges=2650) ;

vector<Point2f>	corners(Mat img,int	bt=20);

};

#endif
