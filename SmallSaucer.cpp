/*
 * SmallSaucer.cpp
 *
 *  Created on: May 4, 2018
 *      Author: parkerqueen
 */

#include "SmallSaucer.h"

//Constructor
SmallSaucer::SmallSaucer(int rad) : Saucer(rad) {
	timer = 0;
}

//Moves the ship and changes direction every 3 seconds
void SmallSaucer::move() {
	if (timer == 3000) {
		timer = 0;
		setDirection(Point());
	}
	Saucer::move();
}

//Logs the time since last direction change
void SmallSaucer::dirTimer() {
	timer += 25;
}

