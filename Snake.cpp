//This is a game of Snake.
//Developed by Miguel Agueda-Cabral.
//Free for all to use, copy, modify, and distribute.


#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <ctime>


// Initialize constants.
const int horiz_lim = 640, vert_lim = 640;
const int body_unit = 20;
const int delay = 100;
int score = 0;
bool gen_food = true;
char no_go_dir = ' ';


cv::Point last_food_pos;
cv::Mat play_env = cv::Mat::zeros(640, 640, CV_8UC3);  // Instantiate blank play environment.


std::list<cv::Point> init_snake(std::list<cv::Point> snake_points) {
	// Initialize snake in game, start with head at center of screen. 
	cv::Point head = cv::Point((horiz_lim / 2), (vert_lim / 2));
	cv::Point tail = cv::Point((head.x - (2 * body_unit)), head.y);

	snake_points.push_front(head);
	snake_points.push_back(tail);

	std::cout << "Init Snake!\n";
	return snake_points;
}


cv::Point generate_food() {
	// Generate a random location for food.
	cv::Point food_pos;
	if (gen_food) {
		food_pos = cv::Point((rand() % 640), (rand() & 640));
		last_food_pos = food_pos;
		gen_food = false;
	}
	return last_food_pos;
}


bool check_food(cv::Point snake_head, cv::Point food_pos) {
	// Check if snake's head is on food.
	if ((abs(snake_head.x - food_pos.x) <= (body_unit / 2)) && (abs(snake_head.y - food_pos.y) <= (body_unit / 2))) {
		score++;
		std::cout << "Got Food! Current Score: ";
		std::cout << score;
		std::cout << '\n';
		gen_food = true;
		return true;
	}
	else
		return false;
}


bool check_head(std::list<cv::Point> snake_points) {
	// Check if head has hit body.
	cv::Point curr_head = snake_points.front();
	snake_points.pop_front();
	for (cv::Point point_on_snake : snake_points) {
		if (curr_head == point_on_snake) {
			std::cout << "Game Over!\n";
			return true;
			break;
		}
	}
	return false;
}


std::list<cv::Point> check_position(std::list<cv::Point> snake_points, cv::Point food_pos) {
	// Check snakes position on screen. Handle out of bounds.
	cv::Point curr_head = snake_points.front();
	cv::Point new_head;
	if (check_head(snake_points)) {  // If snake's head hit the body, exit the game.
		std::cout << "You ate yourself! Game Over\n";
		exit(EXIT_SUCCESS);
	}

	if (check_food(curr_head, food_pos))   // Copy an additional tail to list. 
		snake_points.push_back(snake_points.back());

	if ((curr_head.x >= 0) && (curr_head.x <= horiz_lim) && (curr_head.y >= 0) && (curr_head.y <= vert_lim))
		new_head = curr_head;  // No change when snake head within bounds.
	else {
		if (curr_head.x > horiz_lim)  // Move snakes head to left-most side of screen.
			new_head = cv::Point(0, curr_head.y);

		else if (curr_head.x < 0)  // Move snakes head to right-most side of screen.
			new_head = cv::Point(horiz_lim, curr_head.y);

		if (curr_head.y > vert_lim)  // Move snakes head to top of screen.
			new_head = cv::Point(curr_head.x, 0);

		else if (curr_head.y < 0)  // Move snakes head to bottom of screen.
			new_head = cv::Point(curr_head.x, vert_lim);
	}

	snake_points.push_front(new_head);
	return snake_points;
}


std::list<cv::Point> move_snake(char dir, std::list<cv::Point> snake_points, cv::Point food_pos) {
	// Handle movement of snake's head.
	cv::Point head = snake_points.front();
	no_go_dir = ' ';

	switch (dir) {
	case 'w':
		snake_points.front() -= cv::Point(0, body_unit);
		break;
	case 'a':
		snake_points.front() -= cv::Point(body_unit, 0);
		break;
	case 's':
		snake_points.front() += cv::Point(0, body_unit);
		break;
	case 'd':
		snake_points.front() += cv::Point(body_unit, 0);
		break;
	default:
		break;
	}

	// Handle movement of snake's tail.
	snake_points.pop_back();
	std::list<cv::Point> return_list = check_position(snake_points, food_pos);
	return return_list;
}


cv::Mat draw_snake(cv::Mat play_env, std::list<cv::Point> snake_points, cv::Point food_pos) {
	play_env = cv::Mat::zeros(640, 640, CV_8UC3);  // Blank out existing play env.
	cv::circle(play_env, food_pos, (body_unit / 2), cv::Scalar(0, 0, 255), 2);
	while (snake_points.size() > 1) {
		cv::Point pt1, pt2;
		pt1 = snake_points.front();  // Save first point.
		snake_points.pop_front();  // Then pop first point.
		pt2 = snake_points.front();  // Save second point, do not pop.
		if ((abs(pt2.x - pt1.x) <= body_unit) && (abs(pt2.y - pt1.y) <= body_unit))
			cv::line(play_env, pt1, pt2, cv::Scalar(255, 255, 255), body_unit);
	}

	return play_env;
}


char handle_input(char input) {

	switch (input) {
	case 'w':
		no_go_dir = 's';
		break;
	case 'a':
		no_go_dir = 'd';
		break;
	case 's':
		no_go_dir = 'w';
		break;
	case 'd':
		no_go_dir = 'a';
		break;
	default:
		input = ' ';
		break;
	}

	return input;
}


int main() {
	char input;
	char last_input = ' ';

	cv::Point food_pos;
	std::list<cv::Point> snake_points;

	snake_points = init_snake(snake_points);

	while (true) {
		input = cv::waitKey(delay);
		input = handle_input(input);
		if (input == ' ')
			input = last_input;

		last_input = input;
		food_pos = generate_food();
		snake_points = move_snake(input, snake_points, food_pos);
		play_env = draw_snake(play_env, snake_points, food_pos);

		cv::namedWindow("Snake!", 1);
		cv::imshow("Snake!", play_env);
	}
	cv::destroyAllWindows();
}
