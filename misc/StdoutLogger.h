//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_STDOUTLOGGER_H
#define PGR_PROJECT_STDOUTLOGGER_H

#include "Logger.h"
#include <iostream>
#include <glm/glm.hpp>

/**
 * Logger for standard output.
 *
 * Logging is enabled when the project is compiled with macro "PGR_LOG"
 *
 * @author Petr Flajšingr
 */
class StdoutLogger : public Logger {
 private:
  StdoutLogger() = default;
 public:

  static StdoutLogger &getInstance() {
    static StdoutLogger instance;

    return instance;
  }

  void log(std::string &str) override;
  void logTime(std::string &str) override;
  void log(char *str) override;
  void logTime(char *str) override;
  void log(int val) override;

  void log(glm::vec3 vector);
  void log(glm::vec2 vector);

  void log(char *str, float val);
  void log(char *str, glm::vec3 &vector);

  void log(float value);
};

#endif //PGR_PROJECT_STDOUTLOGGER_H
