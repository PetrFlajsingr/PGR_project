//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <ComplexObject.h>
#include "ClothSim.h"

int width = 17, height = 17;

int tmp = 0;
void PGRsim::ClothSim::prepareClothObject(std::string filePath) {
  auto clothObject = new ComplexObject(10.0f, PGRgraphics::ComplexGraphicsModel::LoadFromOBJ(filePath));

  auto vertexIndices = clothObject->getObjectModel()->getVertexIndices();
  auto vertices = clothObject->getSimVertices();

  if (tmp == 0) {
    clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, 1), 0);
    clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, -1.000000), 272);
  } else {
    clothObject->addConstraint(glm::vec3(-4.37113, 4.24692, 0), 0);
    clothObject->addConstraint(glm::vec3(4.12272, 4.24692, 0), 4160);
    clothObject->addConstraint(glm::vec3(-1.8437, 4.42987, 0.000000), 1300);
    clothObject->addConstraint(glm::vec3(2.04713, 4.47515, 0.000000), 3120);

    clothObject->addConstraint(glm::vec3(-0.381002, -1.810754, 0.012077), 1995);
    clothObject->addConstraint(glm::vec3(-0.379377, -1.949793, 0.012272), 1996);
    clothObject->addConstraint(glm::vec3(-0.377752, -2.088834, 0.012466), 1997);
    clothObject->addConstraint(glm::vec3(-0.376128, -2.227874, 0.012661), 1998);
    clothObject->addConstraint(glm::vec3(-0.374503, -2.366913, 0.012856), 1999);
    clothObject->addConstraint(glm::vec3(-0.372878, -2.505954, 0.013051), 2000);
    clothObject->addConstraint(glm::vec3(-0.371253, -2.644993, 0.013245), 2001);
    clothObject->addConstraint(glm::vec3(-0.369629, -2.784033, 0.013440), 2002);

    std::for_each(
        clothObject->getConstraints().begin() + 4,
        clothObject->getConstraints().end(),
        [this](Constraint *constraint) {
          tearDemoLeft.emplace_back(dynamic_cast<PointConstraint *>(constraint));
        });

    clothObject->addConstraint(glm::vec3(0.181331, -2.360444, -0.006234), 2259);
    clothObject->addConstraint(glm::vec3(0.182955, -2.499485, -0.006039), 2260);
    clothObject->addConstraint(glm::vec3(0.184580, -2.638524, -0.005845), 2261);
    clothObject->addConstraint(glm::vec3(0.186205, -2.777564, -0.005650), 2262);
    clothObject->addConstraint(glm::vec3(0.187830, -2.916605, -0.005455), 2263);
    clothObject->addConstraint(glm::vec3(0.189455, -3.055644, -0.005260), 2264);
    clothObject->addConstraint(glm::vec3(0.191079, -3.194685, -0.005066), 2265);
    clothObject->addConstraint(glm::vec3(0.192704, -3.333724, -0.004871), 2266);

    std::for_each(
        clothObject->getConstraints().begin() + 12,
        clothObject->getConstraints().end(),
        [this](Constraint *constraint) {
          tearDemoRight.emplace_back(dynamic_cast<PointConstraint *>(constraint));
        });
  }

  tmp++;

  float s = 4.0f, d = 2.0f;

  SnappableSpringGroup *group;
  int index;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      index = x * height + y;

      if (y < height - 1) {
        clothObject->addSpring(s, d, index, index + 1);
        group = new SnappableSpringGroup();
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 1]->getCurrectPosition()),
                                   index,
                                   index + 1);
        group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);

        if (x < width - 1) {
          clothObject->addSpring(s, d, index, index + 1);
          group->addSpring(dynamic_cast<SnappableSpring *>(clothObject->getSprings()[clothObject->getSprings().size()
              - 1]));
          clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                   vertices[index + width + 1]->getCurrectPosition()),
                                     index,
                                     index + width + 1);
          group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);

          if (y > 0) {
            clothObject->addSpring(s, d, index, index + 1);
            group->addSpring(dynamic_cast<SnappableSpring *>(clothObject->getSprings()[clothObject->getSprings().size()
                - 1]));
            clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                     vertices[index + width + 1]->getCurrectPosition()),
                                       index,
                                       index + width - 1);
            group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);
          }
        }
      }

      if (x < width - 1) {
        clothObject->addSpring(s, d, index, index + width);
        group->addSpring(dynamic_cast<SnappableSpring *>(clothObject->getSprings()[clothObject->getSprings().size()
            - 1]));
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + width]->getCurrectPosition()),
                                   index,
                                   index + width);
        group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);
      }

      if (y < height - 2) {
        clothObject->addSpring(s, d, index, index + 2);
        group->addSpring(dynamic_cast<SnappableSpring *>(clothObject->getSprings()[clothObject->getSprings().size()
            - 1]));
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2]->getCurrectPosition()),
                                   index,
                                   index + 2);
        group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);
      }

      if (x < width - 2) {
        clothObject->addSpring(s, d, index, index + 2 * width);
        group->addSpring(dynamic_cast<SnappableSpring *>(clothObject->getSprings()[clothObject->getSprings().size()
            - 1]));
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2 * width]->getCurrectPosition()),
                                   index,
                                   index + 2 * width);
        group->addConstraint(clothObject->getConstraints()[clothObject->getConstraints().size() - 1]);
      }
      groups.emplace_back(group);
    }
  }

  for (auto constr : clothObject->getConstraints()) {
    addConstraint(constr);
  }

  for (auto spring : clothObject->getSprings()) {
    addSpring(spring);
  }

  for (auto simVertex : clothObject->getSimVertices()) {
    addObject(simVertex);
  }

  addObject(clothObject);

  width = height = 65;
}
void PGRsim::ClothSim::update(PGRsim::SimTime time) {
  for (auto group : groups) {
    group->check();
  }

  PGRsim::Simulation::update(time);
}
void PGRsim::ClothSim::tear() {
  for (auto constraint : tearDemoLeft) {
    constraint->setPosition(constraint->getPosition() - glm::vec3(0.01f));
  }

  for (auto constraint : tearDemoRight) {
    constraint->setPosition(constraint->getPosition() + glm::vec3(0.01f));
  }
}
void PGRsim::ClothSim::stopTearDemo() {
  for (auto constraint : tearDemoLeft) {
    constraint->disable();
  }

  for (auto constraint : tearDemoRight) {
    constraint->disable();
  }
}
