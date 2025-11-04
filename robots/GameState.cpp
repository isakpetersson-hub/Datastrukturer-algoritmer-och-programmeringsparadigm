/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while(!isEmpty(robot)) {
            *robot = Robot();
        }
        units.push_back(robot);
    }
    teleportHero();
}

GameState::GameState( GameState& other ) {
    units = other.units;
    hero = other.hero;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Unit* unit : units) {
        unit->draw( scene );
    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(&hero));
}

void GameState::moveRobots() {
    for (Unit* unit : units) {
        if (unit->isAlive()) {
            unit->moveTowards(hero.asPoint());
        }
    }
}

void GameState::updateCrashes() {
    for (unsigned i=0; i < units.size(); i++) {
        for ( unsigned o=i+1; o < units.size(); o++) {
            if (units[i]->at(*units[o])) {
                units[i]->doCrash();
                Unit* unit = units[o];
                units.erase(units.begin() + o);
                delete unit;
            }
        }
    }
}

int GameState::countToBeJunked()const{
    int numberDestroyed = 0;
    for (unsigned i=0; i < units.size(); ++i)
        if (units[i]->isToBeJunked())
            numberDestroyed++;

    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for ( unsigned int i = 0; i < units.size(); i++ ) {
        if (units[i]->isToBeJunked()) {
            Junk* junk = new Junk(units[i]->asPoint());
            Unit* unit = units[i];
            units.erase(units.begin() + i);
            delete unit;
            units.push_back(junk);
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for ( const Unit* unit : units ) {
        if ( hero.at( unit->asPoint() ) )
            return true;
    }

    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit* unit) const {
    for (const Unit* gameUnit : units) {
        if (gameUnit->at(*unit))
            return false;
    }

    return true;
}

