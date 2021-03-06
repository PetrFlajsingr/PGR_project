//
// Created by Petr Flajsingr on 2018-12-12.
//

#ifndef PGR_PROJECT_TEARGROUP_H
#define PGR_PROJECT_TEARGROUP_H

#include <SimVertex.h>
#include <springs/Spring.h>
#include <springs/SnappableSpring.h>
#include <constraints/Constraint.h>
#include <ComplexObject.h>

namespace PGRsim {

enum TearOrientation {
  Horizontal, Vertical
};

class TearGroup {
 private:
  SimVertex *vertex;

  SnappableSpring *mainSpring;

  std::vector<Spring *> springs;

  std::vector<DistanceConstraint *> constraints;

  std::vector<DistanceConstraint *> constraintsToDestroy;

  TearOrientation orientation;

  bool torn = false;

 public:
  TearGroup(SimVertex *vertex,
            SnappableSpring *mainSpring,
            TearOrientation orientation);

  /**
   * Add springs which are supposed to be remapped onto the newly created vertex
   * @param spring
   */
  void addSpring(Spring *spring);

  /**
   * Add constraints which are supposed to be remapped onto the newly created vertex.
   * @param constraint
   */
  void addConstraint(DistanceConstraint *constraint);

  void addConstraintToDestroy(DistanceConstraint *constraint);

  /**
   * Check if the main spring has been torn. If yes, create new vertex, add it to ComplexObject,
   * remap constraints and spring.
   *
   * @return new vertex if the main spring has been torn, otherwise nullptr
   */
  SimVertex *check();
};
}

#endif //PGR_PROJECT_TEARGROUP_H
