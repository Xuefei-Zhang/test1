#include"Function.h"

//Slope:输入斜率
float Reading(float Slope)
{
	float instrument_read;
	float current_angle = atanf(Slope);
	float a1, a2;
	//0-1
	if (Slope >= -1.15903&&Slope <= -0.979643)
	{
		//angle
		a1 = atanf(-0.979643);
		a2 = atanf(-1.15903);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1);
	}
	//1-2
	else if (Slope >= -1.37991&&Slope < -1.15903)
	{
		a1 = atanf(-1.15903);
		a2 = atanf(-1.37991);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 1;
	}
	//2-3
	else if (Slope >= -1.60322&&Slope < -1.37991)
	{
		a1 = atanf(-1.37991);
		a2 = atanf(-1.60322);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 2;
	}
	//3-4
	else if (Slope >= -1.86425&&Slope < -1.60322)
	{
		a1 = atanf(-1.60322);
		a2 = atanf(-1.86425);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 3;
	}
	//4-5
	else if (Slope >= -2.1455&&Slope < -1.86425)
	{
		a1 = atanf(-1.86425);
		a2 = atanf(-2.1455);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 4;
	}
	//5-6
	else if (Slope >= -2.45825&&Slope < -2.1455)
	{
		a1 = atanf(-2.1455);
		a2 = atanf(-2.45825);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 5;
	}
	//6-7
	else if (Slope >= -2.8806&&Slope < -2.45825)
	{
		a1 = atanf(-2.45825);
		a2 = atanf(-2.8806);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 6;
	}
	//7-8
	else if (Slope >= -3.38454&&Slope < -2.8806)
	{
		a1 = atanf(-2.8806);
		a2 = atanf(-3.38454);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 7;
	}
	//8-9
	else if (Slope >= -3.95918&&Slope < -3.38454)
	{
		a1 = atanf(-3.38454);
		a2 = atanf(-3.95918);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 8;
	}
	//9-10
	else if (Slope >= -4.7776&&Slope < -3.95918)
	{
		a1 = atanf(-3.95918);
		a2 = atanf(-4.7776);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 9;
	}
	//10-11
	else if (Slope >= -5.94398&&Slope<-4.7776)
	{
		a1 = atanf(-3.95198);
		a2 = atanf(-4.7776);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 10;
	}
	//11-12
	else if (Slope >= -7.44736&&Slope < -5.94398)
	{
		a1 = atanf(-5.94398);
		a2 = atanf(-7.44736);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 11;
	}
	//12-13
	else if (Slope >= -9.25803&&Slope < -7.44736)
	{
		a1 = atanf(-7.44736);
		a2 = atanf(-9.25803);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 12;
	}
	//13-14
	else if (Slope >= -13.3267&&Slope <-9.25803)
	{
		a1 = atanf(-9.25803);
		a2 = atanf(-13.3267);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 13;
	}
	//14-15
	else if (Slope >= -21.1859&&Slope <-13.3267)
	{
		a1 = atanf(-13.3267);
		a2 = atanf(-21.1859);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 14;
	}
	//15-16
	else if (Slope >= -41.6594&&Slope <-21.1859)
	{
		a1 = atanf(-21.1859);
		a2 = atanf(-41.6594);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 15;
	}
	//16-17
	else if (Slope >= -320.544&&Slope <-41.6594)
	{
		a1 = atanf(-41.6594);
		a2 = atanf(-320.544);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 16;
	}
	//17-18   包含斜率为90度
	else if ((Slope > -DBL_MAX&&Slope < -320.544) || (Slope >= 40.3765&&Slope < DBL_MAX))
	{
		a1 = atanf(-320.544);
		a2 = atanf(40.3765);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 17;
	}
	//18-19
	else if (Slope >= 24.365&&Slope <40.3765)
	{
		a1 = atanf(40.3765);
		a2 = atanf(24.365);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 18;
	}
	//19-20
	else if (Slope >= 16.8054&&Slope <24.365)
	{
		a1 = atanf(24.365);
		a2 = atanf(16.8054);
		instrument_read = (1 / abs(a2 - a1))*abs(current_angle - a1) + 19;
	}
	//20-30
	else if (Slope >= 4.59446&&Slope <16.8054)
	{
		a1 = atanf(16.8054);
		a2 = atanf(4.59446);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 20;
	}
	//30-40
	else if (Slope >= 2.99367&&Slope <4.59446)
	{
		a1 = atanf(4.59446);
		a2 = atanf(2.99367);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 30;
	}
	//40-50
	else if (Slope >= 2.46264&&Slope <2.99367)
	{
		a1 = atanf(2.99367);
		a2 = atanf(2.46264);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 40;
	}
	//50-60
	else if (Slope >= 2.13023&&Slope <2.46264)
	{
		a1 = atanf(2.46264);
		a2 = atanf(2.13023);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 50;
	}
	//60-70
	else if (Slope >= 1.92809&&Slope <2.13023)
	{
		a1 = atanf(2.13023);
		a2 = atanf(1.92809);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 60;
	}
	//70-80
	else if (Slope >= 1.77587&&Slope <1.92809)
	{
		a1 = atanf(1.92809);
		a2 = atanf(1.77587);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 70;
	}
	//80-90
	else if (Slope >= 1.68346&&Slope <1.77587)
	{
		a1 = atanf(1.77587);
		a2 = atanf(1.68346);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 80;
	}
	//90-100
	else if (Slope >= 1.60639&&Slope <1.68346)
	{
		a1 = atanf(1.68346);
		a2 = atanf(1.60639);
		instrument_read = (10 / abs(a2 - a1))*abs(current_angle - a1) + 90;
	}
	//100-120
	else if (Slope >= 1.51316&&Slope <1.60639)
	{
		a1 = atanf(1.60639);
		a2 = atanf(1.51316);
		instrument_read = (20 / abs(a2 - a1))*abs(current_angle - a1) + 100;
	}
	//120-140
	else if (Slope >= 1.43915&&Slope <1.51316)
	{
		a1 = atanf(1.51316);
		a2 = atanf(1.43915);
		instrument_read = (20 / abs(a2 - a1))*abs(current_angle - a1) + 120;
	}
	//140-160
	else if (Slope >= 1.37925&&Slope <1.43915)
	{
		a1 = atanf(1.43915);
		a2 = atanf(1.37925);
		instrument_read = (20 / abs(a2 - a1))*abs(current_angle - a1) + 140;
	}
	//160-180
	else if (Slope >= 1.34069&&Slope <1.37925)
	{
		a1 = atanf(1.37925);
		a2 = atanf(1.34069);
		instrument_read = (20 / abs(a2 - a1))*abs(current_angle - a1) + 160;
	}
	//180-200
	else if (Slope >= 1.30093&&Slope <1.34069)
	{
		a1 = atanf(1.34069);
		a2 = atanf(1.30093);
		instrument_read = (20 / abs(a2 - a1))*abs(current_angle - a1) + 180;
	}
	//200-250
	else if (Slope >= 1.23526&&Slope <1.30093)
	{
		a1 = atanf(1.30093);
		a2 = atanf(1.23526);
		instrument_read = (50 / abs(a2 - a1))*abs(current_angle - a1) + 200;
	}
	//250-300
	else if (Slope >= 1.18955&&Slope <1.23526)
	{
		a1 = atanf(1.23526);
		a2 = atanf(1.18955);
		instrument_read = (50 / abs(a2 - a1))*abs(current_angle - a1) + 250;
	}
	//300-400
	else if (Slope >= 1.15015&&Slope <1.18955)
	{
		a1 = atanf(1.18955);
		a2 = atanf(1.15015);
		instrument_read = (100 / abs(a2 - a1))*abs(current_angle - a1) + 300;
	}
	//400-500
	else if (Slope >= 1.12099&&Slope <1.15015)
	{
		a1 = atanf(1.15015);
		a2 = atanf(1.12099);
		instrument_read = (100 / abs(a2 - a1))*abs(current_angle - a1) + 400;
	}
	//500-1000
	else if (Slope >= 1.0662&&Slope <1.12099)
	{
		a1 = atanf(1.12099);
		a2 = atanf(1.0662);
		instrument_read = (500 / abs(a2 - a1))*abs(current_angle - a1) + 500;
	}
	//1000-4000
	else if (Slope >= 1.03161&&Slope <1.0662)
	{
		a1 = atanf(1.0662);
		a2 = atanf(1.03161);
		instrument_read = (3000 / abs(a2 - a1))*abs(current_angle - a1) + 1000;
	}
	return instrument_read;
}

//s,e：一条直线两个端点   HeightImg,WidthImg:图片宽度和高度
//StorePoint：直线延长线两个端点 StorePointOri:相对应的原直线两端点
//功能：得到直线延长线两点
void OnExtensionLine(cv::Point2f s, cv::Point2f e, double HeightImg, double WidthImg, cv::Vec4f& StorePoint, cv::Vec4f& StorePointOri)
{
	cv::Point2f pa, pb;
	cv::Point2f one_a, one_b;
	if (e.x - s.x != 0)
	{
		//Point e is the maximum in the y direction
		if (s.y > e.y)   
		{
			pa = s;
			s = e;
			e = pa;
		}
		//Slope
		double k = (e.y - s.y) / (e.x - s.x); 
		pb = s;
		//Up line
		pa.y = 0, pa.x = s.x - s.y / k; 
		if (pa.x < 0)
		{
			pa.x = 0;
			pa.y = s.y - k*s.x;
		}

		else if (pa.x >= WidthImg)
		{
			pa.x = WidthImg;
			pa.y = s.y + k*(WidthImg - s.x);
		}
		one_a = pa;
		//Down line
		pb.y = HeightImg;  
		pb.x = (HeightImg - e.y) / k + e.x;
		if (pb.x >WidthImg)
		{
			pb.y = e.y + k*(WidthImg - e.x);
			pb.x = WidthImg;
		}

		else if (pb.x < 0)
		{
			pb.y = e.y - k*e.x;
			pb.x = 0;
		}
		one_b = pb;
	}
	if (e.x - s.x == 0)
	{
		if (s.y > e.y)
		{
			pa = s;
			s = e;
			e = pa;
		}
	}
	StorePoint = cv::Vec4f(one_a.x, one_a.y, one_b.x, one_b.y);
	StorePointOri = cv::Vec4f(s.x, s.y, e.x, e.y);	
}

//分类pointCluster(_Angle, PointOri_tmp, cluster_Line, 5);
//src_point contains the angles
void pointCluster(std::vector<float> src_point, std::vector<cv::Vec4f> store_point, std::vector<cluster_str>& cls, float threshold)
{
	cls.clear();
	for (int i = 0; i<src_point.size(); i++)//census the whole lines which through all the other conditions
	{
		//first time
		if (cls.empty() == true)
		{
			cluster_str tmp;
			tmp.centerPoint = src_point.at(i);//_angle
			tmp.points.push_back(src_point.at(i));
			tmp.line_point.push_back(store_point.at(i));//line
			cls.push_back(tmp);
		}
		else
		{
			float current_point = src_point.at(i);
			bool findCluster = false;
			for (int j = 0; j<cls.size(); j++)
			{
				if (abs(cls.at(j).centerPoint - current_point)<threshold)//相差  threshold 度
				{
					cls.at(j).centerPoint = (cls.at(j).centerPoint + current_point) / 2.0f;//caculate average angle
					cls.at(j).points.push_back(current_point);//cluster as one class
					cls.at(j).line_point.push_back(store_point.at(i));
					findCluster = true;
					break;//current point only need be classified to one cluster
				}

			}
			if (findCluster == false)//creat a new cluster
			{
				cluster_str tmp;
				tmp.centerPoint = current_point;
				tmp.points.push_back(current_point);
				tmp.line_point.push_back(store_point.at(i));
				cls.push_back(tmp);
			}

		}
	}
}

