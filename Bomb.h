/*
 * Bomb.h
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Entity.h"

#define BOMB 4

class Bomb : public Entity {
   private:
    static int shp_bspeed;
    float firedDistance;
    int btype;

   public:
    Bomb(Point = Point(), Point = Point(),
         int = SHP_BMB);  // Constructor, creates a bomb at given position and
                          // with given direction
    void move();          // Moves the bomb
    void draw();          // Draws the bomb
    static void setspeed(float);  // Sets the static speed of bomb, static speed
                                  // is the speed of ship bombs
    float distance() const;  // Gives how much distance has the bomb travelled
    int type() const;  // Returns the type of bomb, ship bomb or saucer bomb
};

#endif /* BOMB_H_ */
