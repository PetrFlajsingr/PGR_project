//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_CONSTANTFORCE_H
#define PGR_PROJECT_CONSTANTFORCE_H

#include "ForceGenerator.h"

class ConstantForce : public ForceGenerator {
 private:
  glm::vec3 force;
 public:
  ConstantForce(const glm::vec3 &force);

  void applyForce(SimObject *object) override;

};

#endif //PGR_PROJECT_CONSTANTFORCE_H
