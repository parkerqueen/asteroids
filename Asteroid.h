/*
 * Asteroid.h
 *
 *  Created on: May 2, 2018
 *      Author: parkerqueen
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

#define AST_SMALL 25
#define AST_MED 40
#define AST_LARGE 60

class Asteroid : public Entity {
   public:
    Asteroid(int = AST_LARGE);  // Makes an asteroid at random position
    Asteroid(int, Point &);     // Makes an asteroid at given position
    void constructGeometry();   // Construct the vertices
    int reward() const;         // Returns the reward points
    void draw();                // Draw the asteroid
    int type() const;           // Return the type, complex or simple
    virtual ~Asteroid();        // Destructor
};

#endif /* ASTEROID_H_ */
