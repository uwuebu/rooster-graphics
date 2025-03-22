#include "uniform_buffer.h"

UniformBuffer::UniformBuffer(const std::string& name, GLuint binding_point, GLsizeiptr size)
    : binding_point_(binding_point) {
  glGenBuffers(1, &buffer_id_);
  glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_);
  glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_, buffer_id_);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer() {
  glDeleteBuffers(1, &buffer_id_);
}

void UniformBuffer::Bind() const {
  glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_);
}

void UniformBuffer::Unbind() const {
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetData(GLintptr offset, GLsizeiptr size, const void* data) const {
  glBindBuffer(GL_UNIFORM_BUFFER, buffer_id_);
  glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
