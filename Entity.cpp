/*
 * Entity.cpp
 *
 *  Created on: May 4, 2018
 *      Author: parkerqueen
 */

#include "Entity.h"

long Entity::uidGen = 0;

// Main constructor
Entity::Entity(int rad, int ver) {
    radius = rad;
    vertices = ver;
    speed = GetRandInRange(3, 5);
    setDirection(Point());
    geometry = 0;
    id = uidGen++;
}

// Constructs an entity at given position
Entity::Entity(Point& pos, int rad, int ver) {
    position = pos;
    radius = rad;
    vertices = ver;
    speed = GetRandInRange(3, 5);
    setDirection(Point());
    geometry = 0;
    id = uidGen++;
}

// Constructs a bomb, requires position, direction & type
Entity::Entity(Point& dir, Point& pos, int rad, int btype) {
    radius = rad;
    vertices = 0;
    speed = 11;
    position = pos;
    setDirection(dir);
    if (btype == SHP_BMB) position = dir;
    geometry = 0;
    id = uidGen++;
}

// Returns position
Point& Entity::getPosition() { return position; }

// Returns radius
int Entity::getRadius() const { return radius; }

// Returns ID
long Entity::getId() const { return id; }

// Sets the given direction
void Entity::setDirection(Point dirPoint) {
    float distance;
    direct[0] = dirPoint[0] - position[0];
    direct[1] = dirPoint[1] - position[1];
    distance = sqrt(direct[0] * direct[0] + direct[1] * direct[1]);
    direct[0] = (direct[0] / distance);
    direct[1] = (direct[1] / distance);
}

// Checks if the entity is out of bounds
void Entity::wrapAround() {
    Point hold(position);
    if (position[0] < 0 - radius)
        position[0] = BWIDTH + radius;
    else if (position[0] > BWIDTH + radius)
        position[0] = 0 - radius;
    if (position[1] < 0 - radius)
        position[1] = BHEIGHT + radius;
    else if (position[1] > BHEIGHT + radius)
        position[1] = 0 - radius;
    for (short i = 0;
         i < vertices && (hold[0] != position[0] || hold[1] != position[1]);
         ++i) {
        geometry[i][0] += position[0] - hold[0];
        geometry[i][1] += position[1] - hold[1];
    }
}

// Returns the reward, overridden by some child classes
int Entity::reward() const { return 0; }

// Moves the entity
void Entity::move() {
    position[0] += direct[0] * speed;
    position[1] += direct[1] * speed;
    for (short i = 0; i < vertices; ++i) {
        geometry[i][0] += direct[0] * speed;
        geometry[i][1] += direct[1] * speed;
    }
    wrapAround();
}

// Time Logger, overridden by some child classes
void Entity::dirTimer() { return; }

// Triggers the gun and all bombs, overridden by some child classes
void Entity::triggerGun(Point dir) {}

// Assignment operator
Entity& Entity::operator=(Entity& ent) {
    delete[] geometry;
    position = ent.position;
    vertices = ent.vertices;
    radius = ent.radius;
    speed = ent.speed;
    direct[0] = ent.direct[0];
    direct[1] = ent.direct[1];
    if (vertices != 0) geometry = new Point[vertices];
    for (short i = 0; i < vertices; ++i) geometry[i] = (ent.geometry)[i];
    return *this;
}

// Destructor
Entity::~Entity() { delete[] geometry; }
