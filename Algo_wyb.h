#ifndef _ALGO_WYB_H_
#define _ALGO_WYB_H_

#define RESIZE_TIME 2
#define READ_OR_WRITE 1
#include "opencv2\opencv.hpp"



bool  Algo_wyb_detect(const char* path, cv::Mat ori, cv::Mat& dst, float WYB_Area[8]);



/*-----------------------------------------------------------------------\
|					  万用表函数参数   									 |
| 参数  const string path		  标准模板图像二进制模型路径			 |
|		Mat ori					  实时采集的万用表图像					 |
|		Mat& dst				  矫正检测后的万用表图像				 |
|		返回值			-1	出错										 |
|						 0  正确										 |
\*----------------------------------------------------------------------*/

#endif