#include "parse_xml.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "tinyxml2.h"
#include "triangle.h"
#include "vector3d.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using std::make_shared;

vector3d Parser::getVectFromStr(const char *str) {
  double x, y, z;
  std::sscanf(str, "%lf %lf %lf", &x, &y, &z);
  vector3d vec(x, y, z);
  return vec;
}

Parser::Parser(std::string filename) { doc.LoadFile(filename.c_str()); }

void Parser::setScene() {
  tinyxml2::XMLElement *pRootElement = doc.RootElement();
  const char *tmp =
      pRootElement->FirstChildElement("maxraytracedepth")->GetText();

  int raytracedepth = std::stoi(tmp);
  tmp = pRootElement->FirstChildElement("background")->GetText();

  color bg = getVectFromStr(tmp);

  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("position")
            ->GetText();

  point3d position = getVectFromStr(tmp);

  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("gaze")
            ->GetText();

  vector3d gaze = getVectFromStr(tmp);

  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("up")
            ->GetText();
  vector3d up = getVectFromStr(tmp);

  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("nearplane")
            ->GetText();

  image_plane ip = {0};
  std::sscanf(tmp, "%d %d %d %d", &ip.l, &ip.r, &ip.b, &ip.t);
  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("neardistance")
            ->GetText();

  ip.dist = std::stoi(tmp);

  tmp = pRootElement->FirstChildElement("camera")
            ->FirstChildElement("imageresolution")
            ->GetText();

  std::sscanf(tmp, "%d %d", &ip.nx, &ip.ny);

  scene.setRayDepth(raytracedepth);
  scene.setBG(bg);
  scene.setCamera(Camera(position, gaze, up, ip));

  tinyxml2::XMLElement *materialRoot =
      pRootElement->FirstChildElement("materials");

  for (tinyxml2::XMLElement *mat = materialRoot->FirstChildElement("material");
       mat != nullptr; mat = mat->NextSiblingElement()) {
    int id = mat->FirstAttribute()->IntValue();
    vector3d ambient =
        getVectFromStr(mat->FirstChildElement("ambient")->GetText());

    vector3d diffuse =
        getVectFromStr(mat->FirstChildElement("diffuse")->GetText());

    vector3d specular =
        getVectFromStr(mat->FirstChildElement("specular")->GetText());

    double phong = mat->FirstChildElement("phongexponent")->DoubleText();

    vector3d mirror_reflectance =
        getVectFromStr(mat->FirstChildElement("mirrorreflectance")->GetText());
    scene.insertMaterial(
        Material(id, ambient, diffuse, specular, phong, mirror_reflectance));
  }

  tinyxml2::XMLElement *lightsRoot = pRootElement->FirstChildElement("lights");
  color ambient_light =
      getVectFromStr(lightsRoot->FirstChildElement("ambientlight")->GetText());
  scene.setAmbient(ambient_light);

  for (tinyxml2::XMLElement *point =
           lightsRoot->FirstChildElement("pointlight");
       point != nullptr; point = point->NextSiblingElement()) {
    int id = point->FirstAttribute()->IntValue();
    point3d position =
        getVectFromStr(point->FirstChildElement("position")->GetText());

    vector3d intensity =
        getVectFromStr(point->FirstChildElement("intensity")->GetText());

    PointLightSource p = PointLightSource(id, position, intensity);
    scene.insertPointLight(p);
  }

  std::string vertex(pRootElement->FirstChildElement("vertexdata")->GetText());
  std::stringstream ss(vertex);
  std::string to;
  while (std::getline(ss, to, '\n')) {
    if (!to.empty()) {
      point3d point = getVectFromStr(to.c_str());
      scene.insertVertex(point);
    }
  }

  tinyxml2::XMLElement *mesh_root = pRootElement->FirstChildElement("objects");
  for (tinyxml2::XMLElement *mesh = mesh_root->FirstChildElement("mesh");
       mesh != nullptr; mesh = mesh->NextSiblingElement()) {
    int mesh_id = mesh->FirstAttribute()->IntValue();
    int material_id = mesh->FirstChildElement("materialid")->IntText();
    Mesh _mesh(mesh_id, scene.material_list[material_id - 1]);
    std::string face(mesh->FirstChildElement("faces")->GetText());
    std::stringstream ss(face);
    std::string t;
    while (std::getline(ss, t, '\n')) {
      if (!to.empty()) {
        point3d f = getVectFromStr(t.c_str());
        Triangle triangle(scene.vertex_data[f.x() - 1],
                          scene.vertex_data[f.y() - 1],
                          scene.vertex_data[f.z() - 1]);
        _mesh.add(make_shared<Triangle>(triangle));
      }
    }
    scene.objects.push_back(make_shared<Mesh>(_mesh));
  }
}
