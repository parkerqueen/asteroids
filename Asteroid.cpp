/*
 * Asteroid.cpp
 *
 *  Created on: May 2, 2018
 *      Author: parkerqueen
 */

#include "Asteroid.h"

//Makes an asteroid at random position
Asteroid::Asteroid(int rad) : Entity(rad, GetRandInRange(6, 10)) {
	constructGeometry();
}

//Makes an asteroid at given position
Asteroid::Asteroid(int rad, Point & pos) : Entity(pos, rad, GetRandInRange(6, 10)) {
	constructGeometry();
}

//Constructs the geometry/vertices of the asteroid
void Asteroid::constructGeometry() {
	geometry = new Point[vertices];
	float dtheta = 360 / vertices, stheta = 0;
	for (short i = 0; i < vertices; ++i) {
		float theta = GetRandInRange(stheta, stheta + dtheta);
		geometry[i][0] = position[0] + radius * cos(Deg2Rad(theta));
		geometry[i][1] = position[1] + radius * sin(Deg2Rad(theta));
		stheta += dtheta;
	}
}

//Returns the reward points of the asteroid which are added to score
int Asteroid::reward() const {
	if (radius == AST_SMALL)
		return 10;
	else if (radius == AST_MED)
		return 20;
	return 40;
}

//Draws the asteroid
void Asteroid::draw() {
	for (short i = 0; i < vertices - 1; ++i)
		DrawLine(geometry[i][0], geometry[i][1], geometry[i + 1][0],
				geometry[i + 1][1]);
	DrawLine(geometry[vertices - 1][0], geometry[vertices - 1][1],
			geometry[0][0], geometry[0][1]);
}

//Returns the type of asteroid, simple or complex
int Asteroid::type() const {
	return AST;
}

//Destructor
Asteroid::~Asteroid() {
}
