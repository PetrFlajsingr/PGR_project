//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_CONSTANTFORCE_H
#define PGR_PROJECT_CONSTANTFORCE_H

#include "ForceBase.h"

namespace PGRsim {

/**
 * Apply constant force in the entire area.
 *
 * @author Petr Flajšingr
 */
class ConstantForce : public ForceBase {
 private:
  glm::vec3 force;
 public:
  explicit ConstantForce(const glm::vec3 &force);

  void applyForce(SimObject &object) override;
};
}

#endif //PGR_PROJECT_CONSTANTFORCE_H
