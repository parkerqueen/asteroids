/*
 * Point.h
 *
 *  Created on: 23-Mar-2018
 *      Author: parkerqueen Raza
 */

#ifndef POINT_H_
#define POINT_H_

#include "util.h"

#define BWIDTH 1020
#define BHEIGHT 840

class Point {
   private:
    float x, y;

   public:
    Point();                 // Constructor, random position
    Point(float, float);     // Constructor, given position
    void set(float, float);  // Sets the values
    void setX(float);        // Sets X
    float getX() const;      // Gets X
    void setY(float);        // Sets Y
    float getY() const;      // Gets Y
    void setRandom();        // Sets random values
    float &operator[](int);  // Subscript operator to access values
    float operator[](
        int) const;  // Subscript operator to access values of const Point
    float distance(Point &);  // Returns the distance between two points
};

#endif /* POINT_H_ */
