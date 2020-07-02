/*
 * Saucer.h
 *
 *  Created on: May 3, 2018
 *      Author: parkerqueen
 */

#ifndef SAUCER_H_
#define SAUCER_H_

#include "Entity.h"
#include "Gun.h"

#define SCR_SMALL 30
#define SCR_LARGE 60

class Saucer : public Entity {
   protected:
    Gun gun;

   public:
    Saucer(int = SCR_LARGE);   // Constructor
    void constructGeometry();  // Constructs the geometry
    int reward() const;        // Returns the reward points of the saucer
    void triggerGun(Point = Point());  // Triggers the gun of saucer
    void draw();                       // Draws a saucer
    int type() const;                  // Returns a saucer's type
    Gun& getGun();                     // Returns a saucer's gun
    virtual ~Saucer();                 // Destructor
};

#endif /* SAUCER_H_ */
