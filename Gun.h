/*
 * Gun.h
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#ifndef GUN_H_
#define GUN_H_

#define SCR_FRANG 500

#include "Bomb.h"

class Gun {
   private:
    Bomb *firedB;
    float firingRange;
    int numBombs;

   public:
    Gun();  // Constructor
    void load(Point &, Point &,
              int = SHP_BMB);  // Loads a bomb at given direction and position
    void destroyBomb(long);    // Destroys a bomb with its ID
    void bombspeed(float);     // Sets the speed to be followed by a ship bomb
    bool trigger();  // Triggers the bombs, moves & draws them with some checks
    Bomb *getFiredBombs() const;  // Returns the bombs array
    int getNumBombs() const;      // Returns total number of bombs
    ~Gun();                       // Destructor
};

#endif /* GUN_H_ */
