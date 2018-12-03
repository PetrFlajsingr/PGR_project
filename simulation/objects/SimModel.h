//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H

#include "SimpleGraphicsModel.h"
#include "SimObject.h"

namespace PGRsim {

/**
 * Simulated object with unchangeable shape.
 *
 * Position may be used to create translation matrix for model's vertices.
 */
class SimModel : public SimObject {
 private:
  SimpleGraphicsModel *model;
 public:
  SimModel(float mass, SimObjectType objectType, SimpleGraphicsModel *model);

  void setObjectModel(SimpleGraphicsModel *model) {
    this->model = model;
  }

  SimpleGraphicsModel *getObjectModel() {
    return model;
  }

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_SIMULATEDMODEL_H
