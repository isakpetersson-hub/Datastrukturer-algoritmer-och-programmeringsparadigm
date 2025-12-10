/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

// isape817 rasda103

#include "Hero.h"
#include "constants.h"


Unit* Hero::clone() const {
    return new Hero(*this);
}

bool Hero::isAlive() const {
    return false;
}

void Hero::doCrash() {}

bool Hero::isToBeJunked() const {
    return false;
}

void Hero::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addRect(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                          UNIT_WIDTH, UNIT_HEIGHT), Qt::NoPen, QBrush(HERO_COLOR));
}

