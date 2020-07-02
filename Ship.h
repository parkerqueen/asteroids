/*
 * Ship.h
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Entity.h"
#include "Gun.h"

#define SHIP 30
#define MAXSPEED 20
#define SPINR -5
#define SPINL 5
#define SPNULL 0

class Ship : public Entity {
   private:
    Gun gun;
    int rotAngle, safetyTimer;
    bool fuel, safe, mingled;

   public:
    Ship();                            // Constructor
    void constructGeometry();          // Constructs the geometry of ship
    Point* getVertices() const;        // Returns the vertices of ship
    void triggerGun(Point = Point());  // Triggers the ship's gun
    void accelarate(bool);  // Sets if a fuel is being accelarated or not
    void spin(float);       // Sets if a ship is to be rotated
    void setSafety(bool);   // Sets if the ship is invincible or not
    bool isSafe()
        const;         // Returns if the ship is invincible at the moment or not
    void recenter();   // Recenters the ship
    void setRandom();  // Randomly positions the ship
    void mingle();     // Animates the ship destruction
    void hyperdrive();        // Calls the hyperdrive functionality
    bool isMingled() const;   // Returns if the ship is destroyed
    void timer();             // Logs the time to turn safety off
    void move();              // Moves the ship
    void draw();              // Draws the ship
    void loadGun();           // Loads the ship's gun
    float shipspeed() const;  // Returns the ship's speed
    void rotate(float);       // Actually rotates the ship
    int type() const;         // Returns the type
    Gun& getGun();            // Returns the ship's gun
};

#endif /* SHIP_H_ */
