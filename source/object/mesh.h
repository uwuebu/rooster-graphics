#ifndef MESH_H_
#define MESH_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector, std::cout, std::endl;

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  string type;
  string path;
};

class Mesh {
public:
  // mesh data
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;
  Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
  //void Draw(Shader& shader);
private:
  // render data
  unsigned int VAO, VBO, EBO;
  //void setupMesh();
};

inline Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  //setupMesh();
}
#endif