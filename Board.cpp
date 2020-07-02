/*
 * Board.cpp
 *
 *  Created on: May 2, 2018
 *      Author: parkerqueen
 */

#include "Board.h"

// Constructs the board
Board::Board(int w, int h) {
    over = true;
    width = w;
    height = h;
    level = 1;
    scoreThresh = 4000;
    cooldown = score = numScr = 0;
    lives = T_LIVES;
    buildBoard(false);
}

// Builds the board for a new game
void Board::buildBoard(bool flag) {
    if (flag) {
        level = 1;
        lives = T_LIVES;
        score = 0;
    }
    timeParam = 0;
    numAst = num = GetRandInRange(2, 3) + level;
    entities = new Entity *[num];
    for (short i = 0; i < num; ++i)
        entities[i] = (GetRandInRange(0, 10) % 2 == 0) ? new Asteroid
                                                       : new ComplexAsteroid;
    ship = new Ship;
}

// Adds an asteroid at given pos of given type
void Board::addAsteroid(int type, int size, Point pos) {
    ++num;
    ++numAst;
    Entity **temp = entities;
    entities = new Entity *[num];
    for (short i = 0; i < num - 1; ++i) entities[i] = temp[i];
    if (type == -1)
        entities[num - 1] = (GetRandInRange(0, 10) % 2 == 0)
                                ? new Asteroid(size, pos)
                                : new ComplexAsteroid(size, pos);
    else if (type == 0)
        entities[num - 1] = new Asteroid(size, pos);
    else
        entities[num - 1] = new ComplexAsteroid(size, pos);
    delete[] temp;
}

// Adds a saucer to the array of entities
void Board::addSaucer() {
    ++num;
    ++numScr;
    Entity **temp = entities;
    entities = new Entity *[num];
    for (short i = 0; i < num - 1; ++i) entities[i] = temp[i];
    entities[num - 1] =
        (GetRandInRange(0, 10) % 2 == 0) ? new Saucer : new SmallSaucer;
    delete[] temp;
}

// Removes any given entity from the array if its ID is given
void Board::removeEntity(long id) {
    for (short i = 0; i < num; ++i)
        if (entities[i]->getId() == id) {
            --num;
            Entity **temp = entities;
            entities = new Entity *[num];
            for (short j = 0, k = 0; j < num + 1; ++j)
                if (i != j) {
                    entities[k] = temp[j];
                    ++k;
                }
            delete temp[i];
            delete[] temp;
            break;
        }
}

// Breaks an asteroid into smaller sub asteroids
void Board::breakAsteroid(Entity *ast) {
    int type = AST;
    if (ast->type() == AST) type = CXA;
    if (ast->getRadius() == AST_LARGE)
        for (short i = 0; i < 4 / (type + 1); ++i)
            addAsteroid(type, AST_MED, ast->getPosition());
    else if (ast->getRadius() == AST_MED)
        for (short i = 0; i < 4 / (type + 1); ++i)
            addAsteroid(type, AST_SMALL, ast->getPosition());
}

// Main runner function to simulate all functionality except collission & timing
void Board::run() {
    if (!over) {
        if (!numAst) {
            exit();
            ++level;
            buildBoard(false);
        }
        ship->move();
        ship->draw();
        ship->triggerGun();
    }
    for (short i = 0; i < num; ++i) {
        entities[i]->move();
        entities[i]->draw();
        entities[i]->triggerGun(ship->getPosition());
    }
    drawBars();
}

// Check if the ship bombs collide with any entity
void Board::shipBombsCollission() {
    Bomb *shipBombs = ship->getGun().getFiredBombs();
    int shipNumBombs = ship->getGun().getNumBombs();
    for (short i = 0; i < shipNumBombs; ++i) {
        for (short j = 0; j < num; ++j)
            if (shipBombs[i].getPosition().distance(
                    entities[j]->getPosition()) <= entities[j]->getRadius()) {
                if (entities[j]->type() == AST || entities[j]->type() == CXA) {
                    breakAsteroid(entities[j]);
                    --numAst;
                } else
                    --numScr;
                score += entities[j]->reward();
                if (score > scoreThresh) {
                    ++lives;
                    scoreThresh += scoreThresh;
                }
                removeEntity(entities[j]->getId());
                ship->getGun().destroyBomb(shipBombs[i].getId());
                Mix_PlayChannel(-1, explosion, 0);
                break;
            }
    }
}

// Checks if Saucer bombs collide with the ship
void Board::saucerBombsCollission() {
    for (short i = 0; i < num; ++i) {
        if (entities[i]->type() == SCR) {
            Saucer *scr = (Saucer *)entities[i];
            Bomb *saucerBomb = scr->getGun().getFiredBombs();
            int numBombs = scr->getGun().getNumBombs();
            if (numBombs && saucerBomb->getPosition().distance(
                                ship->getPosition()) <= ship->getRadius()) {
                if (!(--lives)) over = true;
                ship->setSafety(true);
                ship->mingle();
                scr->getGun().destroyBomb(saucerBomb->getId());
                Mix_PlayChannel(-1, explosion, 0);
                break;
            }
        }
    }
    if (over) exit();
}

// Checks if the ship collides with any entity
void Board::shipAccidentCollission() {
    bool cont = true;
    for (short i = 0; i < num && cont; ++i) {
        Point *verts = ship->getVertices();
        for (short j = 0; j < 3; ++j) {
            if (entities[i]->getPosition().distance(verts[j]) <=
                entities[i]->getRadius()) {
                if (!(--lives)) over = true;
                ship->setSafety(true);
                ship->mingle();
                Mix_PlayChannel(-1, explosion, 0);
                cont = false;
                break;
            }
        }
    }
    if (over) exit();
}

// Calls all the collission functions
void Board::collider() {
    if (!over) {
        if (!ship->isSafe()) shipAccidentCollission();
        if (!over) shipBombsCollission();
        if (!over && !ship->isSafe()) saucerBombsCollission();
    }
}

// Calls the timer functions of all entities and adds saucers time to time
void Board::timer(int t) {
    if (!over) {
        cooldown += t;
        timeParam += t;
        if (timeParam > 30000 && numScr < level) {
            timeParam = 0;
            addSaucer();
        }
        ship->timer();
    }
    for (short i = 0; i < num; ++i) entities[i]->dirTimer();
}

// Fuels the ship
void Board::fuelShip(bool fuel) {
    if (!over && (!ship->isMingled() || fuel == false)) ship->accelarate(fuel);
}

// Rotates the ship
void Board::rotate(float ang) {
    if (!over && (!ship->isMingled() || ang == SPNULL)) ship->spin(ang);
}

// Calls the hyperdrive functionality
void Board::hyperdrive() {
    if (!over && (!ship->isMingled())) ship->hyperdrive();
}

// Draws the needed strings
void Board::drawBars() {
    if (!over) {
        DrawString(15, BHEIGHT - 30, "SCORE: " + Num2Str(score), colors[WHITE]);
        for (short i = 0, j = 0; i < lives; ++i, j += 20)
            DrawString(200 + j, BHEIGHT - 30, "A", colors[WHITE]);
        DrawString(BWIDTH - 200, BHEIGHT - 30,
                   "SPEED: " + Num2Str(ship->shipspeed()) + " MPH",
                   colors[WHITE]);
        DrawRectangle(BWIDTH - 420, BHEIGHT - 35,
                      (ship->shipspeed() / MAXSPEED) * 200, 30, colors[TEAL]);
        DrawString(BWIDTH - 100, 40, "Level: " + Num2Str(level), colors[WHITE]);
    } else {
        if (!lives) {
            DrawString(BWIDTH / 2 - 150, BHEIGHT / 2 + 200,
                       "YOU LOST! Total Score: " + Num2Str(score), colors[RED]);
            DrawString(BWIDTH / 2 - 180, BHEIGHT / 2 + 150,
                       "Ship VF-01 Is Ready to Relaunch!", colors[WHITE]);
        }
        DrawString(BWIDTH / 2 - 200, BHEIGHT / 2 + 50,
                   "The Asteroids Are Very Angry Today!", colors[WHITE]);
        DrawString(BWIDTH / 2 - 170, BHEIGHT / 2, "Press Enter to Wage WARRRR!",
                   colors[WHITE]);
    }
}

// Loads the ship gun
void Board::shoot() {
    if (!over && !ship->isSafe() && cooldown >= 100) {
        ship->loadGun();
        cooldown = 0;
    }
}

// Restarts the game if not already over
void Board::start() {
    if (over) {
        over = false;
        exit();
        buildBoard(true);
    }
}

// Deletes all the entities and resets everything
void Board::exit() {
    for (short i = 0; i < num; ++i) delete entities[i];
    delete ship;
    delete[] entities;
    entities = 0;
    ship = 0;
    num = numScr = numAst = 0;
}

// Destructor
Board::~Board() { exit(); }
