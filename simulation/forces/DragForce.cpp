//
// Created by Petr on 29.11.2018.
//

#include "DragForce.h"

void DragForce::applyForce(SimObject *object) {
    object->setResultantForce(object->getResultantForce() - dragCoefficient * object->getVelocity());
}
