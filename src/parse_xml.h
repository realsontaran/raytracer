#ifndef PARSE_XML_H_
#define PARSE_XML_H_
#include "camera.h"
#include "scene.h"
#include "tinyxml2.h"
#include "vector3d.h"
#include <string>

class Parser {
public:
  Parser() {}
  Parser(std::string filename);
  void setScene();
  Scene getScene() { return scene; }

private:
  vector3d getVectFromStr(const char *str);
  tinyxml2::XMLDocument doc;
  Scene scene;
};

#endif // PARSE_XML_
