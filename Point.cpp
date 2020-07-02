/*
 * Point.cpp
 *
 *  Created on: 23-Mar-2018
 *      Author: parkerqueen Raza
 */

#include "Point.h"

//Constructor, random position
Point::Point() {
	setRandom();
}

//Constructor, given position
Point::Point(float x, float y) {
	set(x, y);
}

//Sets the given values
void Point::set(float x, float y) {
	this->x = x;
	this->y = y;
}

//Sets X
void Point::setX(float x) {
	this->x = x;
}

//Gets X
float Point::getX() const {
	return x;
}

//Sets Y
void Point::setY(float y) {
	this->y = y;
}

//Gets Y
float Point::getY() const {
	return y;
}

//Sets random values excluding 200 px square area around center for the ship's first spawn
void Point::setRandom() {
	x = GetRandInRange(50, BWIDTH - 50);
	y = GetRandInRange(50, BHEIGHT - 50);
	if (x > (BWIDTH / 2) - 200 && x < (BWIDTH / 2) + 200
			&& y > (BHEIGHT / 2) - 200 && y < (BHEIGHT / 2) + 200)
		setRandom();
}

//Subscript operator for non const Point
float & Point::operator[](int axis) {
	if (axis == 0)
		return x;
	else
		return y;
}

//Subscript operator for const Point
float Point::operator[](int axis) const {
		return (axis == 0) ? x : y;
}

//Returns the distance between two Points
float Point::distance(Point & point) {
	return sqrt((x - point[0]) * (x - point[0]) + (y - point[1]) * (y - point[1]));
}
