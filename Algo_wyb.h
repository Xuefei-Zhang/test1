#ifndef _ALGO_WYB_H_
#define _ALGO_WYB_H_

#define RESIZE_TIME 2
#define READ_OR_WRITE 1
#include "opencv2\opencv.hpp"



bool  Algo_wyb_detect(const char* path, cv::Mat ori, cv::Mat& dst, float WYB_Area[8]);



/*-----------------------------------------------------------------------\
|					  ���ñ�������   									 |
| ����  const string path		  ��׼ģ��ͼ�������ģ��·��			 |
|		Mat ori					  ʵʱ�ɼ������ñ�ͼ��					 |
|		Mat& dst				  ������������ñ�ͼ��				 |
|		����ֵ			-1	����										 |
|						 0  ��ȷ										 |
\*----------------------------------------------------------------------*/

#endif