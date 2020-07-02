/*
 * SmallSaucer.h
 *
 *  Created on: May 4, 2018
 *      Author: parkerqueen
 */

#ifndef SMALLSAUCER_H_
#define SMALLSAUCER_H_

#include "ComplexAsteroid.h"
#include "Saucer.h"

class SmallSaucer : public Saucer {
   private:
    int timer;

   public:
    SmallSaucer(int = SCR_SMALL);  // Constructor
    void move();                   // Moves the small saucer
    void dirTimer();  // Timer to help change direction every 3 secondss
};

#endif /* BIGSAUCER_H_ */
