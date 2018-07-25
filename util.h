
#ifndef _SIFT_WANYONGBIAO_DETECT_H_
#define _SIFT_WANYONGBIAO_DETECT_H_

#include <stdio.h>
#include <vector>
#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>



using namespace std;
using namespace cv;
using namespace xfeatures2d;
void drawMatch(Mat srcColorImage, Mat dstColorImage, vector<Point2f> &srcPoints, vector<Point2f> &dstPoints);
cv::Mat findInliers(vector<KeyPoint> &qKeypoints, vector<KeyPoint> &objKeypoints, vector<DMatch> &matches, Mat queryImage, Mat dstColorImage, float WYB_Area[8]);
cv::Mat findInliers(vector<KeyPoint> &qKeypoints, vector<KeyPoint> &objKeypoints, vector<DMatch> &matches, const int query_cols, const int query_rows, Mat dstColorImage, float WYB_Area[8]);
Mat ExtractSIFTFeature(Mat img, vector<KeyPoint> &points);
#endif