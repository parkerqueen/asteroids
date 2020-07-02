/*
 * Board.h
 *
 *  Created on: May 5, 2018
 *      Author: parkerqueen
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <cstdio>
#include <iostream>

#include "ComplexAsteroid.h"
#include "Ship.h"
#include "SmallSaucer.h"
#include "util.h"

#define T_LIVES 3

using namespace std;

class Board {
   private:
    bool over;
    int width, height, num, numScr, numAst, timeParam, lives, score, level,
        scoreThresh, cooldown;
    Entity **entities;
    Ship *ship;

   public:
    Board(int, int);        // Constructs the board
    void buildBoard(bool);  // Prepared the board for a new game
    void addAsteroid(
        int = -1, int = AST_LARGE,
        Point = Point());  // Adds an asteroid of given size at given position
    void addSaucer();      // Adds a saucer
    void removeEntity(long);       // Removes any entity, given its id
    void breakAsteroid(Entity *);  // Breaks an asteroid into smaller asteroids
    void run();                    // Main runner function
    void shipBombsCollission();  // Checks if ship bombs collide with any entity
    void
    saucerBombsCollission();  // Checks if saucer bombs collide with the ship
    void shipAccidentCollission();  // Checks if ship collides with any entity
    void collider();                // Calls all the collision functions
    void timer(int);      // Calls the timer functionality of all entities
    void fuelShip(bool);  // Fuels the ship
    void rotate(float);   // Rotates the ship
    void hyperdrive();    // Calls the hyperdrive functionality
    void setShoot(bool);  // Sets the shooting on or off
    void drawBars();      // Draws the strings
    void shoot();         // Loads the gun
    void start();         // Restarts/Starts the game
    void exit();          // Deletes all entities
    ~Board(void);         // Destructor
};

#endif
