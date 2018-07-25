#ifndef FUNCTION_H
#define FUNCTION_H
#include"StructData.h"

float Reading(float Slope);
void OnExtensionLine(cv::Point2f s, cv::Point2f e, double HeightImg, double WidthImg,cv::Vec4f& StorePoint,cv::Vec4f& StorePointOri);
void pointCluster(std::vector<float> src_point, std::vector<cv::Vec4f> store_point, std::vector<cluster_str>& cls, float threshold);

#endif