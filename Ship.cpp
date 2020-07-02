/*
 * Ship.cpp
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#include "Ship.h"

//Constructor, sets the position to center & some flags to false
Ship::Ship() :
		Entity(SHIP, 4) {
	position.set(BWIDTH / 2, BHEIGHT / 2);
	constructGeometry();
	setDirection(geometry[1]);
	direct[0] = direct[1] = safetyTimer = 0;
	rotAngle = fuel = mingled = safe = false;
	speed = 1;
}

//Constructs the ship's geometry
void Ship::constructGeometry() {
	geometry = new Point[vertices];
	float dtheta = 150, theta = 0;
	for (short i = 0; i < vertices; ++i) {
		float sub = (i == 3) ? 15 : 0;
		geometry[i][0] = position[0] + (radius - sub) * cos(Deg2Rad(theta));
		geometry[i][1] = position[1] + (radius - sub) * sin(Deg2Rad(theta));
		theta += dtheta - ((i == 2) ? 120 : 0);
	}
	rotate(-60);
}

//Returns the ship's vertices
Point * Ship::getVertices() const {
	return geometry;
}

//Triggers the ship's gun and all its bombs
void Ship::triggerGun(Point dir) {
	gun.trigger();
}

//Sets if the ship is being accelarated
void Ship::accelarate(bool give) {
	fuel = give;
}

//Sets if the ship is to be rotated
void Ship::spin(float ang) {
	rotAngle = ang;
}

//Sets if the ship is invincible or not
void Ship::setSafety(bool safety) {
	safe = safety;
}

//Returns true if the ship is safe, false otherwise
bool Ship::isSafe() const {
	return safe;
}

//Recenters the ship
void Ship::recenter() {
	position.set(BWIDTH / 2, BHEIGHT / 2);
	delete[] geometry;
	constructGeometry();
}

void Ship::setRandom() {
	position.setRandom();
	delete[] geometry;
	constructGeometry();
}

//Animates ship destruction
void Ship::mingle() {
	mingled = true;
	for (short i = 0; i < vertices; ++i) {
		geometry[i][0] += GetRandInRange(-30, 30);
		geometry[i][1] += GetRandInRange(-30, 30);
	}
}

//Calls the hyperdrive functionality
void Ship::hyperdrive() {
	position.setRandom();
	delete[] geometry;
	constructGeometry();
}

//Returns if the ship is destroyed
bool Ship::isMingled() const {
	return mingled;
}

void Ship::timer() {
	if (safe) {
		if ((safetyTimer += 25) >= 2500) {
			safe = false;
			safetyTimer = 0;
		}
		if (safetyTimer >= 1000 && mingled) {
			recenter();
			mingled = false;
		}
	}
}

//Moves the ship
void Ship::move() {
	if ((int) rotAngle != 0)
		rotate(rotAngle);
	if (fuel) {
		Mix_PlayChannel(-1, thrust, 0);
		Point hold(direct);
		setDirection(geometry[1]);
		direct[0] += hold[0];
		direct[1] += hold[1];
	}
	direct[0] *= 0.95;
	direct[1] *= 0.95;
	Entity::move();
	gun.bombspeed(shipspeed() + 10);
}

//Draws the ship
void Ship::draw() {
	if (!mingled) {
		for (short i = 0; i < vertices - 1; ++i)
			DrawLine(geometry[i][0], geometry[i][1], geometry[i + 1][0],
					geometry[i + 1][1]);
		DrawLine(geometry[vertices - 1][0], geometry[vertices - 1][1],
				geometry[0][0], geometry[0][1]);
	} else {
		DrawLine(geometry[1][0], geometry[1][1], position[0], position[1]);
		DrawLine(geometry[2][0], geometry[2][1], geometry[0][0], geometry[0][1]);
	}
}

//Loads the ship's gun with a new bomb
void Ship::loadGun() {
	gun.load(geometry[1], position);
}

//Gets the ship speed
float Ship::shipspeed() const {
	return sqrt(direct[0] * direct[0] + direct[1] * direct[1]);
}

//Actually rotates the ship
void Ship::rotate(float angle) {
	Point vector;
	angle = Deg2Rad(angle);
	for (short i = 0; i < vertices; ++i) {
		vector.set(geometry[i][0] - position[0], geometry[i][1] - position[1]);
		geometry[i][0] = (vector[0] * cos(angle) - vector[1] * sin(angle))
				+ position[0];
		geometry[i][1] = (vector[0] * sin(angle) + vector[1] * cos(angle))
				+ position[1];
	}
}

//Returns the entity type
int Ship::type() const {
	return SHP;
}

//Returns ship's gun
Gun & Ship::getGun() {
	return gun;
}
