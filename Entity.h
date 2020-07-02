/*
 * Entity.h
 *
 *  Created on: May 4, 2018
 *      Author: parkerqueen
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Point.h"

#define AST 0
#define CXA 1
#define SCR 2
#define SHP 3
#define SHP_BMB 4
#define SCR_BMB 5

class Entity {
   protected:
    static long uidGen;
    Point position, *geometry, direct;
    int vertices, radius;
    long id;
    float speed;

   public:
    Entity(int, int);           // Main constructor
    Entity(Point &, int, int);  // Constructs an entity at given pos
    Entity(Point &, Point &, int,
           int);               // Constructs a bomb, needs position & direction
    Point &getPosition();      // Returns the position
    int getRadius() const;     // Returns the radius
    long getId() const;        // Returns the ID
    void setDirection(Point);  // Sets the direction
    void wrapAround();         // Checks if an entity is out of bounds
    virtual int reward() const;  // Returns the reward points of an entity,
                                 // overridden by child classes
    virtual void move();         // Moves the entity
    virtual void dirTimer();     // Time Logger, overridden by child classes
    virtual void triggerGun(
        Point = Point());     // Triggers the gun, overridden by child classes
    virtual void draw() = 0;  // Draws the entity, pure virtual, implemented by
                              // each child class
    virtual int type() const = 0;  // Returns the type, pure virtual,
                                   // implemented by each child class
    Entity &operator=(Entity &);   // Assignment operator
    virtual ~Entity();             // Destructor
};

#endif /* ENTITY_H_ */
