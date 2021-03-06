//
// Created by Petr on 29.11.2018.
//

#include <StdoutLogger.h>
#include "Spring.h"

PGRsim::Spring::Spring(float stiffness, float damping, SimObject *simulatedObjectA,
                       SimObject *simulatedObjectB) : stiffness(stiffness), damping(damping),
                                                      simulatedObjectA(simulatedObjectA),
                                                      simulatedObjectB(simulatedObjectB) {
  restLength = glm::length(simulatedObjectA->getCurrectPosition() - simulatedObjectB->getCurrectPosition());
  currentLength = restLength;
}

void PGRsim::Spring::applyForce(SimObject &object) {
  applyForce();
}

void PGRsim::Spring::applyForce() {
  direction = simulatedObjectA->getCurrectPosition() - simulatedObjectB->getCurrectPosition();

  if (direction != glm::vec3(0, 0, 0)) {
    currentLength = glm::length(direction);
    direction = glm::normalize(direction);

    force = -stiffness * ((currentLength - restLength) * direction);
    force +=
        -damping * glm::dot(simulatedObjectA->getResultantForce() - simulatedObjectB->getResultantForce(), direction)
            * direction;

    if (simulatedObjectA->getSimulatedObjectType() != Shape) {
      simulatedObjectA->setResultantForce(simulatedObjectA->getResultantForce() + force);
    }
    if (simulatedObjectB->getSimulatedObjectType() != Shape) {
      simulatedObjectB->setResultantForce(simulatedObjectB->getResultantForce() - force);
    }
  }
}

PGRsim::Spring::~Spring() = default;
