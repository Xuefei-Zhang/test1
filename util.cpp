



#include "util.h"
Mat ExtractSIFTFeature(Mat img, vector<KeyPoint> &points) {
	//auto img = imread(imgfn, true);    //imgfn: image file name const string &imgfn
	//resize(img, img, Size(320, 240));
	/*      SIFT         */
	//Ptr<SiftFeatureDetector> detector = SiftFeatureDetector::create();
	//vector<KeyPoint> keypoints;

	//detector->detect(img, keypoints);
	//Ptr<SiftDescriptorExtractor> descriptor_extractor = SiftDescriptorExtractor::create();
	//Mat descriptors;
	//if (!keypoints.size()) {
	//	return Mat();
	//}

	//// extract sift feature
	//descriptor_extractor->compute(img, keypoints, descriptors);
	////points.resize(keypoints.size());
	//for (int i = 0; i < keypoints.size(); i++) {
	//	points.push_back(keypoints[i]);
	//}
	
	//*******ORB********//
	Ptr<ORB>detector = ORB::create(5000);
	vector<KeyPoint>keypoints;
	detector->detect(img, keypoints);
	Mat descriptors;
	if (keypoints.empty())
	{
		return Mat();
	}
	detector->compute(img, keypoints, descriptors);
	//points.resize(keypoints.size());
	for (int i = 0; i < keypoints.size(); i++)
	{
		points.push_back(keypoints[i]);
	}
	drawKeypoints(img, points, img);
	
	imwrite("./10.jpg", img);
	//waitKey(0);
	return descriptors;


	/*      SURF          */
	//Ptr<SurfFeatureDetector>detector_surf = SurfFeatureDetector::create();
	//vector<KeyPoint>keypoints_surf;
	//
	//detector_surf->detect(img, keypoints_surf);
	//Ptr<SurfDescriptorExtractor>descriptor_surf = SurfDescriptorExtractor::create();
	//Mat descriptors_surf;
	//if (!keypoints_surf.size()) {
	//	return Mat();
	//}
	//
	//// extract sift feature
	//descriptor_surf->compute(img, keypoints_surf, descriptors_surf);
	////points.resize(keypoints.size());
	//for (int i = 0; i < keypoints_surf.size(); i++) {
	//	points.push_back(keypoints_surf[i]);
	//}
	////drawKeypoints(img, points, img);
	//
	////imwrite("./10.jpg", img);
	////imshow("10", img);
	////waitKey(0);
	//return descriptors_surf;


}
// 画匹配的特征点对
void drawMatch(Mat srcColorImage, Mat dstColorImage, vector<Point2f> &srcPoints, vector<Point2f> &dstPoints) {
	// https://gist.github.com/thorikawa/3398619
	/*Mat srcColorImage = imread(src);
	Mat dstColorImage = imread(obj);*/

	// Create a image for displaying mathing keypoints
	Size sz = Size(srcColorImage.size().width + dstColorImage.size().width, srcColorImage.size().height + dstColorImage.size().height);
	Mat matchingImage = Mat::zeros(sz, CV_8UC3);

	// Draw camera frame
	Mat roi1 = Mat(matchingImage, Rect(0, 0, srcColorImage.size().width, srcColorImage.size().height));
	srcColorImage.copyTo(roi1);
	// Draw original image
	Mat roi2 = Mat(matchingImage, Rect(srcColorImage.size().width, srcColorImage.size().height, dstColorImage.size().width, dstColorImage.size().height));
	dstColorImage.copyTo(roi2);

	// Draw line between nearest neighbor pairs
	for (int i = 0; i < (int)srcPoints.size(); ++i) {
		Point2f pt1 = srcPoints[i];
		Point2f pt2 = dstPoints[i];
		Point2f from = pt1;
		Point2f to = Point(srcColorImage.size().width + pt2.x, srcColorImage.size().height + pt2.y);
		line(matchingImage, from, to, Scalar(0, 255, 255));
	}
	// Display mathing image
	resize(matchingImage, matchingImage, Size(matchingImage.cols / 2, matchingImage.rows / 2));
	//namedWindow("Display frame", CV_WINDOW_AUTOSIZE);
	namedWindow("Matched Points", 2);
	imshow("Matched Points", matchingImage);
	cvWaitKey(0);
}

cv::Mat findInliers(vector<KeyPoint> &qKeypoints, vector<KeyPoint> &objKeypoints, vector<DMatch> &matches, const int query_cols, const int query_rows, Mat dstColorImage, float WYB_Area[8]) {
	// 获取关键点坐标
	vector<Point2f> queryCoord;
	vector<Point2f> objectCoord;
	for (int i = 0; i < matches.size(); i++) {
		queryCoord.push_back((qKeypoints[matches[i].queryIdx]).pt);
		objectCoord.push_back((objKeypoints[matches[i].trainIdx]).pt);
	}
	//imshow("dstcolorimage", dstColorImage);
	// 使用自定义的函数显示匹配点对
	//drawMatch(imgfn, objFileName, queryCoord, objectCoord);
	//Mat srcColorImage = imread(imgfn);
	//Mat dstColorImage = imread(objFileName);
	/*resize(dstColorImage, dstColorImage, Size(200, 200) );
	imshow("1", dstColorImage);
	waitKey(0);*/
	/*imshow("ori", dstColorImage);
	waitKey(0);*/
	// 计算homography矩阵
	Mat mask;
	vector<Point2f> queryInliers;
	vector<Point2f> sceneInliers;
	Mat H = findHomography(objectCoord, queryCoord, mask, CV_RANSAC);
	//std::cout << "h.size()=" << h.size() << endl;
	Mat img_dst_tmp, img_black_seged_tmp;//进行透射变换矫正图像

										 //if (h.rows != 3 || h.cols != 3) //返回二值图和轮廓图
										 //{
										 //	return CyAlgoContourErr;
										 //}
										 //warpPerspective(dstColorImage, img_dst_tmp, H, cv::Size(1100, 1100));
										 //Mat H = findHomography( queryCoord, objectCoord, CV_RANSAC, 10, mask);
										 //imshow("mask", mask);

	int inliers_cnt = 0, outliers_cnt = 0;
	for (int j = 0; j < mask.rows; j++) {
		if (mask.at<uchar>(j) == 1) {
			queryInliers.push_back(queryCoord[j]);
			//cout << queryCoord[j].x << "  " << queryCoord[j].y <<"   "<< objectCoord[j].x << "  " << objectCoord[j].y << endl;
			sceneInliers.push_back(objectCoord[j]);

			inliers_cnt++;
		}
		else {
			outliers_cnt++;
		}
	}
	//cout << queryInliers.size() << endl;
	//cout << queryCoord.size() << endl;
	Mat h = findHomography(queryInliers, sceneInliers);
	// Mat h2 = findHomography(sceneInliers, queryInliers);
	//std::cout << "h.size()=" << h.size() << endl;

	vector<Point2f>p1(4);
	p1[0] = cvPoint(0, 0);
	p1[1] = cvPoint(query_cols, 0);
	p1[2] = cvPoint(0, query_rows);
	p1[3] = cvPoint(query_cols, query_rows);
	vector<Point2f>p2(4);
	perspectiveTransform(p1, p2, h);
	
	//WYB_Area assigment
	WYB_Area[0] = p2[0].x;
	WYB_Area[1] = p2[0].y;
	WYB_Area[2] = p2[1].x;
	WYB_Area[3] = p2[1].y;
	WYB_Area[4] = p2[2].x;
	WYB_Area[5] = p2[2].y;
	WYB_Area[6] = p2[3].x;
	WYB_Area[7] = p2[3].y;

	//for (int i = 0; i < 4; i++)
	//{
	//	circle(dstColorImage, p2[i], 3, Scalar(0, 0, 255), 3);
	//}
	/* Rect rec1 = boundingRect(p2);
	Mat detectimg = dstColorImage(rec1);*/
	warpPerspective(dstColorImage, img_dst_tmp, H, cv::Size(query_cols, query_rows));
	/*imshow("point", dstColorImage);
	namedWindow("matched", 2);
	imshow("matched", img_dst_tmp);
	waitKey(0);*/
	//drawMatch(srcColorImage, dstColorImage, queryInliers, sceneInliers);
	return img_dst_tmp;
}

cv::Mat findInliers(vector<KeyPoint> &qKeypoints, vector<KeyPoint> &objKeypoints, vector<DMatch> &matches, Mat queryImage, Mat dstColorImage, float WYB_Area[8]) {
	// 获取关键点坐标
	vector<Point2f> queryCoord;
	vector<Point2f> objectCoord;
	for (int i = 0; i < matches.size(); i++) {
		queryCoord.push_back((qKeypoints[matches[i].queryIdx]).pt);
		objectCoord.push_back((objKeypoints[matches[i].trainIdx]).pt);
	}
	// 使用自定义的函数显示匹配点对
	//drawMatch(imgfn, objFileName, queryCoord, objectCoord);
	//Mat srcColorImage = imread(imgfn);
	//Mat dstColorImage = imread(objFileName);
	/*resize(dstColorImage, dstColorImage, Size(200, 200) );
	imshow("1", dstColorImage);
	waitKey(0);*/
	/*imshow("ori", dstColorImage);
	waitKey(0);*/
	// 计算homography矩阵
	Mat mask;
	vector<Point2f> queryInliers;
	vector<Point2f> sceneInliers;
	Mat H = findHomography(objectCoord, queryCoord, mask, CV_RANSAC);
	//std::cout << "h.size()=" << h.size() << endl;
	Mat img_dst_tmp, img_black_seged_tmp;//进行透射变换矫正图像

										 //if (h.rows != 3 || h.cols != 3) //返回二值图和轮廓图
										 //{
										 //	return CyAlgoContourErr;
										 //}
										 //warpPerspective(dstColorImage, img_dst_tmp, H, cv::Size(1100, 1100));
										 //Mat H = findHomography( queryCoord, objectCoord, CV_RANSAC, 10, mask);
										 //imshow("mask", mask);

	int inliers_cnt = 0, outliers_cnt = 0;
	for (int j = 0; j < mask.rows; j++) {
		if (mask.at<uchar>(j) == 1) {
			queryInliers.push_back(queryCoord[j]);
			//cout << queryCoord[j].x << "  " << queryCoord[j].y <<"   "<< objectCoord[j].x << "  " << objectCoord[j].y << endl;
			sceneInliers.push_back(objectCoord[j]);

			inliers_cnt++;
		}
		else {
			outliers_cnt++;
		}
	}
	//cout << queryInliers.size() << endl;
	//cout << queryCoord.size() << endl;
	Mat h = findHomography(queryInliers, sceneInliers);
	// Mat h2 = findHomography(sceneInliers, queryInliers);
	//std::cout << "h.size()=" << h.size() << endl;

	vector<Point2f>p1(4);
	p1[0] = cvPoint(0, 0);
	p1[1] = cvPoint(queryImage.cols, 0);
	p1[2] = cvPoint(0, queryImage.rows);
	p1[3] = cvPoint(queryImage.cols, queryImage.rows);
	vector<Point2f>p2(4);
	perspectiveTransform(p1, p2, h);

	//WYB_Area assigment
	WYB_Area[0] = p2[0].x;
	WYB_Area[1] = p2[0].y;
	WYB_Area[2] = p2[1].x;
	WYB_Area[3] = p2[1].y;
	WYB_Area[4] = p2[2].x;
	WYB_Area[5] = p2[2].y;
	WYB_Area[6] = p2[3].x;
	WYB_Area[7] = p2[3].y;
	//for (int i = 0; i < 4; i++)
	//{
	//	circle(dstColorImage, p2[i], 3, Scalar(0, 0, 255), 3);
	//}
	/* Rect rec1 = boundingRect(p2);
	Mat detectimg = dstColorImage(rec1);*/
	warpPerspective(dstColorImage, img_dst_tmp, H, cv::Size(queryImage.cols, queryImage.rows));
	/*imshow("point", dstColorImage);
	namedWindow("matched", 2);
	imshow("matched", img_dst_tmp);
	waitKey(0);
	drawMatch(srcColorImage, dstColorImage, queryInliers, sceneInliers);*/
	return img_dst_tmp;
}