#ifndef UNIFORM_BUFFER_H_
#define UNIFORM_BUFFER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class UniformBuffer {
 public:
  UniformBuffer(const std::string& name, GLuint binding_point, GLsizeiptr size);
  ~UniformBuffer();

  void Bind() const;
  void Unbind() const;

  void SetData(GLintptr offset, GLsizeiptr size, const void* data) const;

 private:
  GLuint buffer_id_;
  GLuint binding_point_;
};

#endif  // UNIFORM_BUFFER_H_
