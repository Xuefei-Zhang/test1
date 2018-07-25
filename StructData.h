#ifndef STRUCTDATA_H
#define STRUCTDATA_H
#include <opencv2/opencv.hpp>
#include<vector>
#include<iostream>
struct cluster_str
{
	float centerPoint;
	std::vector<float> points;
	std::vector<cv::Vec4f> line_point;
};

#endif