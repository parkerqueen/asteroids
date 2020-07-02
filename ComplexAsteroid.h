/*
 * ComplexAsteroid.h
 *
 *  Created on: May 2, 2018
 *      Author: parkerqueen
 */

#ifndef COMPLEXASTEROID_H_
#define COMPLEXASTEROID_H_

#include "Asteroid.h"

class ComplexAsteroid : public Asteroid {
   private:
    int timer;

   public:
    ComplexAsteroid(int = AST_LARGE);  // Constructs a complex asteroid
    ComplexAsteroid(
        int, Point &);  // Constructs a complex asteroid at given position
    void move();        // Moves the asteroid
    void dirTimer();    // Timer to help change direction every three seconds
    int type() const;   // Returns the type which is CXA (Complex Asteroid)
};

#endif /* COMPLEXASTEROID_H_ */
