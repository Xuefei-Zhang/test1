#include"AlgoPointerRecg.h"
#include"Algo_wyb.h"
#include <opencv2/core/ocl.hpp>

#define Length_Threshold 18
#define Slope_Threshold 0.9
using namespace cv;

#ifdef _WIN32
int __stdcall PointerRec(char* Image_Path, char* Model_Path, float& WYB_data, float WYB_Area[8])
#else
int  PointerRec(char* Image_Path, char* Model_Path, float& WYB_data, float WYB_Area[8])
#endif
{
	ocl::setUseOpenCL(false);
	cv::Mat SoureceImg = cv::imread(Image_Path);

	cv::Mat ObjectImg;
	bool _UseRefine =false;
	bool _Test= Algo_wyb_detect(Model_Path, SoureceImg, ObjectImg,WYB_Area);//source: full image; objectimage: after detect+calibrate
	//加入判断？？


	cv::Mat SoureceGray;
	cvtColor(ObjectImg, SoureceGray, CV_BGR2GRAY);

	//Detection dial plate ,_Dial:上表盘
	cv::Mat _Dial = SoureceGray(cv::Rect(0, 0, SoureceGray.cols, SoureceGray.rows*0.45));
	//LSD line detection 
	cv::Ptr<cv::LineSegmentDetector> line_Dec = _UseRefine ? cv::createLineSegmentDetector(cv::LSD_REFINE_ADV) : 
		cv::createLineSegmentDetector(cv::LSD_REFINE_NONE);

	std::vector< cv::Vec4f> lines_std;
	line_Dec->detect(_Dial, lines_std);	
	//std::cout << "lines_std=" << lines_std.size() << std::endl;
	
	//Remove short lines by Line length
	std::vector< cv::Vec4f> line_one;
	for (int i = 0; i < lines_std.size(); i++)
	{
		float Len = sqrt((lines_std[i][2] - lines_std[i][0])*(lines_std[i][2] - lines_std[i][0]) +
			(lines_std[i][3] - lines_std[i][1])* (lines_std[i][3] - lines_std[i][1]));//one element of line_std contain <point<x1,y1>,point<x2,y2>>
		if (Len > Length_Threshold)
		{
			line_one.push_back(lines_std[i]);
		}
	}

	//Set a threshold based on the slope to remove the non-conforming line
	std::vector<cv::Vec4f> line_two;
	for (int i = 0; i < line_one.size(); i++)
	{
		//斜率存在
		if ((line_one[i][2] - line_one[i][0]) != 0)
		{
			float tangent = (line_one[i][3] - line_one[i][1]) / (line_one[i][2] - line_one[i][0]);
			if (tangent > Slope_Threshold || tangent < -Slope_Threshold)
			{
				line_two.push_back(line_one[i]);
			}
		}
	}	
	//Exclude lines by extending the pointer over a specific area 
	cv::Rect CommonRoi = cv::Rect(_Dial.cols*0.358, _Dial.rows - 20, 0.3*_Dial.cols, 20);//the centroid area
	std::vector<cv::Vec4f> PointEtn_tmp;
	std::vector<cv::Vec4f> PointOri_tmp;
	cv::Vec4f SigPoint_tmp;
	cv::Vec4f SigPointOri_tmp;
	double _DialHeight = _Dial.rows;
	double _DialWidth = _Dial.cols;

	for (int i = 0; i < line_two.size(); i++)
	{
		//detect if it through the centroid area
		OnExtensionLine(cv::Point2f(line_two[i][0], line_two[i][1]), cv::Point2f(line_two[i][2], line_two[i][3]), _DialHeight,
			_DialWidth, SigPoint_tmp, SigPointOri_tmp);
		if((SigPoint_tmp[0]>= CommonRoi.x&& SigPoint_tmp[0] <= CommonRoi.x + CommonRoi.width&&
			SigPoint_tmp[1] >= CommonRoi.y&&SigPoint_tmp[1] <= CommonRoi.y+ CommonRoi.height) ||
			(SigPoint_tmp[2] >=CommonRoi.x&&SigPoint_tmp[2] <= CommonRoi.x + CommonRoi.width&&
			SigPoint_tmp[3] >= CommonRoi.y&&SigPoint_tmp[3] <= CommonRoi.y + CommonRoi.height))//decide if the line through the specific area
		{
			PointEtn_tmp.push_back(SigPoint_tmp);
			PointOri_tmp.push_back(SigPointOri_tmp);
		}
	}


	//only one line
	std::vector<float> _Angle;
	std::vector<cluster_str> cluster_Line;
	std::vector<float> distance_sum;
	cv::Point2f Line_start;
	cv::Point2f Line_end;
	if (PointOri_tmp.size() > 1)
	{
		//caculate the angles
		for (int j = 0; j < PointOri_tmp.size(); j++)
		{
			if (PointOri_tmp[j][2] - PointOri_tmp[j][0] != 0)
			{
				float Slope_temp = (PointOri_tmp[j][3] - PointOri_tmp[j][1]) / (PointOri_tmp[j][2] - PointOri_tmp[j][0]);
				float Angle_temp = atanf(Slope_temp) * 180 / 3.1415926;
				//为负时，加上180度，区间[0-180]
				if (Slope_temp < 0)
				{
					Angle_temp = Angle_temp + 180;
				}
				_Angle.push_back(Angle_temp);
			}
			if (PointOri_tmp[j][2] - PointOri_tmp[j][0] == 0)
			{
				float Slope_temp_one = 90;
				_Angle.push_back(Slope_temp_one);
			}
		}
		//Classfication
		pointCluster(_Angle, PointOri_tmp, cluster_Line, 5);

		//caculate the sum length of each cluster's lines
		for (int i = 0; i < cluster_Line.size(); i++)
		{
			cluster_str tmp;
			tmp = cluster_Line.at(i);
			float currentDistance = 0;
			for (int j = 0; j < tmp.line_point.size(); j++)
			{
				cv::Vec4f current_line_point = tmp.line_point.at(j);
				float distance_tmp = sqrt(pow(current_line_point[0] - current_line_point[2], 2) + pow(current_line_point[1] - current_line_point[3], 2));
				currentDistance = currentDistance + distance_tmp;
			}
			distance_sum.push_back(currentDistance);
		}

		int max_indx = 0;
		float max_distance = 0;
		for (int i = 0; i < distance_sum.size(); i++)
		{
			if (i == 0)
			{
				max_indx = 0;
				max_distance = distance_sum.at(i);
			}
			else
			{
				if (distance_sum.at(i) > max_distance)
				{
					max_indx = i;
					max_distance = distance_sum.at(i);
				}
			}
		}

		cluster_str select_clus = cluster_Line.at(max_indx);
		cv::Vec4f PointEtn_tmp_1;
		cv::Vec4f PointOri_tmp_1;
		std::vector<cv::Vec4f> FinPointEtn;
		std::vector<cv::Vec4f> FinPointOri;
		for (int i = 0; i < select_clus.line_point.size(); i++)//cluster may contain more than one line
		{		
			OnExtensionLine(cv::Point2f(select_clus.line_point[i][0], select_clus.line_point[i][1]),
				cv::Point2f(select_clus.line_point[i][2], select_clus.line_point[i][3]), _DialHeight,
				_DialWidth, PointEtn_tmp_1, PointOri_tmp_1);

			FinPointEtn.push_back(PointEtn_tmp_1);
			FinPointOri.push_back(PointOri_tmp_1);
		}
		//caculate average line
		for (int i = 0; i <  FinPointEtn.size(); i++)
		{
			Line_start.x += FinPointEtn[i][0];
			Line_start.y += FinPointEtn[i][1];
			Line_end.x += FinPointEtn[i][2];
			Line_end.y += FinPointEtn[i][3];
		}
		Line_start.x = Line_start.x / FinPointEtn.size();
		Line_start.y = Line_start.y / FinPointEtn.size();
		Line_end.x = Line_end.x / FinPointEtn.size();
		Line_end.y = Line_end.y / FinPointEtn.size();

	}
	
	else if (PointOri_tmp.size() == 1)
	{
		Line_start.x = PointOri_tmp[0][0];
		Line_start.y = PointOri_tmp[0][1];
		Line_end.x = PointOri_tmp[0][2];
		Line_end.y = PointOri_tmp[0][3];
	}

	else if (PointOri_tmp.size() == 0)
	{
		//std::cout << "Failed to detect the pointer, please select the picture again............";
		//getchar();
		return -1;
	}
	//imshow("objimg_1", ObjectImg);
	line(ObjectImg, Line_start, Line_end, Scalar(250, 0, 0));
	imwrite("./line_img.jpg", ObjectImg);
	float Slope_final;
	if (Line_end.x - Line_start.x != 0)
	{
		Slope_final = (Line_end.y - Line_start.y) / (Line_end.x - Line_start.x);
		float Angle_final = atanf(Slope_final);
		if (Angle_final < 0)
		{
			Angle_final = Angle_final + 180;
		}
		if (Angle_final<atanf(1.03161)||Angle_final>(atanf(-1.15903)+180))
		{
		//std::cout << "Beyond the range, please select the picture again............" << std::endl;
		//getchar();
		return -1;
		}
		Angle_final *= 180 / 3.4159226;
		//std::cout << "Angle_final: " << Angle_final << std::endl;
		WYB_data = Reading(Slope_final);
	}
	//Slope not exist(17-18)
	if (Line_end.x - Line_start.x == 0)
	{
		float a3 = atanf(-320.544);
		float a4 = atanf(40.3765);
		WYB_data = (1 / abs(a4 - a3))*abs(90 - a3) + 17;
	}

	return 0;
}