//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "SimpleGraphicsModel.h"
PGRgraphics::SimpleGraphicsModel *PGRgraphics::SimpleGraphicsModel::LoadFromFile(std::string path) {
  std::string msg = "Loading object from: " + path;
  StdoutLogger::getInstance().logTime(msg);
  auto model = new SimpleGraphicsModel();

  tinyobj::attrib_t attribs;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string error;
  if (!tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, &error, path.c_str())) {
    std::cerr << "Loading object failed: " + error << std::endl;
    return nullptr;
  }

  model->indices = shapes[0].mesh.indices;

  model->normals.resize(attribs.vertices.size());

  std::for_each(model->normals.begin(), model->normals.end(),
                [](glm::vec3 &value) {
                  value = glm::vec3(0.0f);
                });

  for (auto indice : model->indices) {
    model->vertexIndices.emplace_back(indice.vertex_index);
    model->normals[indice.vertex_index] += glm::vec3(attribs.normals[indice.normal_index * 3],
                                                     attribs.normals[indice.normal_index * 3 + 1],
                                                     attribs.normals[indice.normal_index * 3 + 2]);
    if(indice.texcoord_index != -1) {
      model->texCoords[indice.vertex_index] = glm::vec2(attribs.texcoords[indice.texcoord_index * 2], attribs.texcoords[indice.texcoord_index * 2 + 1]);
    }
  }

  std::for_each(model->normals.begin(), model->normals.end(),
                [](glm::vec3 &value) {
                  value = glm::normalize(value);
                });

  for (int i = 0; i < attribs.vertices.size(); i += 3) {
    model->vertices.emplace_back(glm::vec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
  }

  model->position = glm::vec3(0, 0, 0);

  return model;
}

PGRgraphics::SimpleGraphicsModel *PGRgraphics::SimpleGraphicsModel::LoadFromOBJ(std::string path) {
  auto model = LoadFromFile(path);
  model->color = glm::vec3(RandomGenerator::getInstance().getRandomNumber(),
                           RandomGenerator::getInstance().getRandomNumber(),
                           RandomGenerator::getInstance().getRandomNumber());
  return model;
}

PGRgraphics::SimpleGraphicsModel *PGRgraphics::SimpleGraphicsModel::LoadFromOBJ(std::string path, glm::vec3 color) {
  auto model = LoadFromFile(path);
  model->color = color;
  return model;
}

void PGRgraphics::SimpleGraphicsModel::setPosition(const glm::vec3 &position) {
  SimpleGraphicsModel::position = position;
}

const glm::vec3 &PGRgraphics::SimpleGraphicsModel::getPosition() const {
  return position;
}

glm::mat4 PGRgraphics::SimpleGraphicsModel::getTranslationMatrix() {
  return glm::translate(model, position);
}
