// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/opencv.hpp>
#include <iostream>


cv::Mat play_env;


int main()
{
	std::cout << "This is a game of Snake.\n";

	play_env = cv::Mat::ones(640, 640, CV_8U);
	
	if (play_env.empty())
	{
		std::cout << "Image is empty. Exiting\n";
		return -1;
	}

	cv::namedWindow("Snake!", 1);

	while (true)
	{
		cv::imshow("Snake!", play_env);
		cv::waitKey(0);
	}

	cv::destroyAllWindows();

}
