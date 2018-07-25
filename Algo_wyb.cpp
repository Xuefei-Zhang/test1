#include "Algo_wyb.h"
#include "string.h"
#include"util.h"
#include<fstream>
bool Algo_wyb_detect(const char* path, cv::Mat ori, cv::Mat& dst, float WYB_Area[8])
{
	string image_dat_path = path;
	string point_dat_path = path;
	image_dat_path = image_dat_path + "/" + "std_image.dat";
	point_dat_path = point_dat_path + "/" + "std_image_point.dat";
	Mat   qDescriptor;
	Mat   objDesriptor;
	vector<KeyPoint> qKeypoints;
	vector<KeyPoint> objKeypoints;
	
#if READ_OR_WRITE ==1
	/*char* filename_des = ;
	char* filename_poi = { "std_image_point.dat" };*/
	ofstream out_des, out_poi;
	string image_path = path;
	string imgfn =image_path+"/"+ "s.jpg";
	Mat queryImage;
	queryImage = imread(imgfn);

	out_des.open(image_dat_path, ofstream::binary);
	out_poi.open(point_dat_path, ofstream::binary);


	/*vector<float>vec1, vec2, vec3;*/

	//imwrite("std.jpg", queryImage);
	//imshow("std", queryImage);

	qDescriptor = ExtractSIFTFeature(queryImage, qKeypoints);
	//cout << qDescriptor << endl;
	//std::cout << qDescriptor.depth();
	Point2f pt;
#ifdef WIN32
	if (!out_des && !out_poi)
	{
		std::cout << "fail to open file" << endl;
	}
#endif

	/* write the binary*/
	int channel = qDescriptor.channels();
	out_des.write(reinterpret_cast<const char*>(&channel), sizeof(int) * 1);//save the four byte memory of file for one integer
	int depth = qDescriptor.depth();
	out_des.write(reinterpret_cast<const char*>(&depth), sizeof(int) * 1);
	out_des.write(reinterpret_cast<const char*>(&qDescriptor.cols), sizeof(int) * 1);
	out_des.write(reinterpret_cast<const char*>(&qDescriptor.rows), sizeof(int) * 1);
	out_des.write(reinterpret_cast<const char*>(&queryImage.cols), sizeof(int) * 1);
	out_des.write(reinterpret_cast<const char*>(&queryImage.rows), sizeof(int) * 1);


	for (int i = 0; i < qDescriptor.rows; i++)
	{
		out_des.write(reinterpret_cast<const char*>(qDescriptor.ptr(i)), qDescriptor.cols*qDescriptor.elemSize());
	}
	int size = qKeypoints.size();
	out_poi.write(reinterpret_cast<const char*>(&size), 1 * sizeof(int));
	for (int i = 0; i < qKeypoints.size(); i++)
	{
		pt = qKeypoints[i].pt;
		out_poi.write(reinterpret_cast<const char*>(&pt), sizeof(float) * 2);
	}


#else if READ_OR_WRITE ==2



	ifstream in_des(image_dat_path, ifstream::binary | ifstream::ate);//默认定位指针位于文件末，所以第一次调用tellg函数时，返回的定位指针也可以作为流大小
	ifstream in_poi(point_dat_path, ifstream::binary | ifstream::ate);
	/*char* p;
	int channel1[4];
	in_des.read((char*)&channel1, sizeof(int)*4);
	*/

	bool open = in_des.is_open();
	if (!in_des)
	{
		return false;
	}
		//cout << "CAN'T OPEN  std_image.dat" << endl;
		

	if (!in_poi)
	{
		return false;
	}


	/*first*/
	streampos size1 = in_des.tellg();
	in_des.seekg(0, ifstream::beg);
	int* arguments = new int[6];
	in_des.read((char*)arguments, 6 * sizeof(int));
	streampos size2 = in_des.tellg();//cur position
	char* memory = new char[size1 - size2];//creat a new memory
	in_des.read(memory, size1 - size2);
	float *mat_des = (float*)memory;



	/*get the default arguments*/
	int channel = arguments[0], col = arguments[2], row = arguments[3], depth = arguments[1],queryImage_cols=arguments[4],queryImage_rows=arguments[5];
	
	
	/*recover the descriptor Mat */
	int type = CV_MAKE_TYPE(depth, channel);
	Mat descriptor(Size(col, row), type);
	for (size_t i = 0; i < row; i++)
	{
		float* data = descriptor.ptr<float>(i);
		for (size_t j = 0; j < col*channel; j++)
		{
			data[j] = *(mat_des);
			mat_des++;
		}
	}
	
	//cout << descriptor << endl;
	qDescriptor = descriptor;

	/*second*/
	streampos size3 = in_poi.tellg();//tellg response the current position of pointer, also response the size of cur stream
									 //当前定位指针位于end，所以指针也就是stream大小
	in_poi.seekg(0, ifstream::beg);//first argu means the streamoff, the sec is base address which can be ios::beg/ios::end/ios::cur
								   //重定位到beg，定位指针位于文件头
	int size;

	in_poi.read(reinterpret_cast<char*>(&size), sizeof(int) * 1);
	streampos size4 = in_poi.tellg();
	char* memory2 = new char[size3 - size4];
	in_poi.read(memory2, size3 - size4);
	Point2f *vec_poi = (Point2f*)memory2;
	
	
	for (int i = 0; i < size; i++)
	{
		KeyPoint tmp(*vec_poi,0 );
		qKeypoints.push_back(tmp);
		if (i != size - 1)
			vec_poi++;
	}
	delete[]memory2;
	delete[]memory;
	delete[]arguments;
#endif
	
	
	/*if (ori.cols >= 1920)
	time = 2;
	else  time = 1;*/
	resize(ori, ori, cv::Size(ori.cols / RESIZE_TIME, ori.rows / RESIZE_TIME));
	/*introducing std image*/

	
	
	/*ori image*/

	objDesriptor = ExtractSIFTFeature(ori, objKeypoints);

	//FlannBasedMatcher matcher;
	BFMatcher bfmatcher;
	vector<Point2f> qeK, obK;
	vector<vector<DMatch>> matches;
	vector<DMatch> matches2;
	vector<DMatch> good_matches2;
	//matcher.knnMatch(qDescriptor, objDesriptor, matches, 2);
	bfmatcher.match(qDescriptor, matches2, objDesriptor);

	//Matching
	/*vector<DMatch> matches;
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	matcher->match(qDescriptor, objDesriptor, matches);*/
	cout << "find out total " << matches2.size() << " matches" << endl;

	//bfmatcher.match(qDescriptor, objDesriptor, matches);
	/*for (size_t i = 0; i < matches2.size(); i++) {
		if (matches[i][0].distance < 0.8*matches[i][1].distance) {
			good_matches2.push_back(matches[i][0]);
			qeK.push_back(qKeypoints[matches[i][0].queryIdx].pt);
			obK.push_back(objKeypoints[matches[i][1].trainIdx].pt);
		}
	}*/
#if READ_OR_WRITE ==1
	dst = findInliers(qKeypoints, objKeypoints, good_matches2, queryImage, ori, WYB_Area);
#elif READ_OR_WRITE ==2
	dst = findInliers(qKeypoints, objKeypoints, matches2, queryImage_cols, queryImage_rows, ori, WYB_Area);

#endif
	if (dst.empty())

		return -1;
	else

		return 0;
}