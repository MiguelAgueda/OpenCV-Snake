// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>

bool up = false, down = false, left = false, right = false;
cv::Mat play_env = cv::Mat::zeros(640, 640, CV_8UC3);  // Instantiate blank play environment.
char head_dir = 'd', tail_dir = 'd';
int head_pos_y = 320, head_pos_x = 0, tail_pos_y, tail_pos_x;
std::list <cv::Point> snake_points;


void init_snake()
{
	snake_points.push_front(cv::Point(320, 5));
	snake_points.push_back(cv::Point(320, 0));
}


cv::Point handle_dir(char dir)
{
	cv::Point point_to_return;
	if (dir != head_dir)
	{
		switch (head_dir)
		{
		case 'w':
			point_to_return = cv::Point(0, -10);
			break;

		case 'a':
			point_to_return = cv::Point(-10, 0);
			break;

		case 's':
			point_to_return = cv::Point(10, 0);
			break;

		case 'd':
			point_to_return = cv::Point(0, 10);
			break;

		default:
			// Return something!
			break;
		}

		//switch (tail_dir)
		//{
		//case 'w':
		//	break;

		//case 'a':
		//	break;

		//case 's':
		//	break;

		//case 'd':
		//	break;

		//default:
		//	break;
		//}

		return point_to_return;
	}
}


std::list<cv::Point> move_snake(char dir, std::list<cv::Point> snake_points) {
	std::list<cv::Point> new_points = snake_points;
	char last_dir;

	// Handle movement of snake's head.
	cv::Point head = snake_points.front();
	switch (dir) {
	case 'w':
		head -= cv::Point(0, 10);
		break;
	case 'a':
		head -= cv::Point(10, 0);
		break;
	case 's':
		head += cv::Point(0, 10);
		break;
	case 'd':
		head += cv::Point(10, 0);
		break;
	default:
		break;
	}

	new_points.push_front(head);  // Push new head to front of list.

	// Handle movement of snake's tail.
	new_points.pop_back();
	return new_points;

}


cv::Mat draw_snake(cv::Mat play_env, std::list<cv::Point> snake_points) {
	play_env = cv::Mat::zeros(640, 640, CV_8UC3);  // Blank out existing play env.
	std::list<cv::Point> copy_snake_points = snake_points;

	while (copy_snake_points.size() > 1)
	{
		cv::Point pt1, pt2;
		pt1 = copy_snake_points.front();  // Save first point.
		copy_snake_points.pop_front();  // Then pop first point.
		pt2 = copy_snake_points.front();  // Save second point, do not pop.
		cv::line(play_env, pt1, pt2, cv::Scalar(255, 255, 255), 10);
	}
	return play_env;
}

//void inc_len(char dir)
//{
//	switch (dir)
//	{
//	case 'w':
//		for (cv::Point point : snake_lines);
//	}
//}


int main() {
	cv::namedWindow("Snake!", 1);
	init_snake();
	while (true)
	{
		char input = cv::waitKey(100);
		if (input != ' ')
			std::cout << input;
		snake_points = move_snake(input, snake_points);
		play_env = draw_snake(play_env, snake_points);
		cv::imshow("Snake!", play_env);
	}
}

void diag_line() {
	std::cout << "This is a game of Snake.\n";

	play_env = cv::Mat::zeros(640, 640, CV_8UC3);

	if (play_env.empty())
	{
		std::cout << "Image is empty. Exiting\n";
	}
	cv::Point free_point;
	cv::Point piv_point = cv::Point((640 / 2), (640 / 2));


	cv::namedWindow("Snake!", 1);
	int i = 0;

	while (true)
	{
		i++;

		if (i > 640)
			i = 0;

		std::cout << "Value of i: ";
		std::cout << i + '\n';
		free_point = cv::Point(i, i);
		cv::line(play_env, piv_point, free_point, cv::Scalar(255, 255, 255), 10);

		cv::imshow("Snake!", play_env);
		cv::waitKey(1);
	}

	cv::destroyAllWindows();
}
