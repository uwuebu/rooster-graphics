#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>  // include glad to get the required OpenGL headers
#include <glm/glm.hpp>  // include glm for matrix and vector operations

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Shader {
 public:
  // the program ID
  unsigned int id;

  // constructor reads and builds the shader
  Shader() = default;
  Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path = nullptr);

  // use/activate the shader
  void Use();

  // utility uniform functions
  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetMat4(const std::string& name, const glm::mat4& mat) const;
  void SetVec3(const std::string& name, const glm::vec3& value) const;
  void SetVec3(const std::string& name, float x, float y, float z) const;
  void SetFloatArray(const std::string& name, const std::vector<float>& values) const;
  void SetVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const;
  void SetMat4Array(const std::string& name, const std::vector<glm::mat4>& values) const;

 private:
  void CheckCompileErrors(GLuint shader, const std::string& type) const;
};

inline Shader::Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertex_code;
  std::string fragment_code;
  std::string geometry_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;
  std::ifstream g_shader_file;
  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  g_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    v_shader_file.open(vertex_path);
    f_shader_file.open(fragment_path);
    std::stringstream v_shader_stream, f_shader_stream;
    // read file's buffer contents into streams
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
    // if geometry shader path is present, also load a geometry shader
    if (geometry_path != nullptr) {
      g_shader_file.open(geometry_path);
      std::stringstream g_shader_stream;
      g_shader_stream << g_shader_file.rdbuf();
      g_shader_file.close();
      geometry_code = g_shader_stream.str();
    }
  } catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
  }
  const char* v_shader_code = vertex_code.c_str();
  const char* f_shader_code = fragment_code.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &v_shader_code, nullptr);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &f_shader_code, nullptr);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");
  // if geometry shader is given, compile geometry shader
  unsigned int geometry;
  if (geometry_path != nullptr) {
    const char* g_shader_code = geometry_code.c_str();
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &g_shader_code, nullptr);
    glCompileShader(geometry);
    CheckCompileErrors(geometry, "GEOMETRY");
  }
  // shader Program
  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  if (geometry_path != nullptr) glAttachShader(id, geometry);
  glLinkProgram(id);
  CheckCompileErrors(id, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  if (geometry_path != nullptr) glDeleteShader(geometry);
}

inline void Shader::Use() {
  glUseProgram(id);
}

inline void Shader::SetBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

inline void Shader::SetInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

inline void Shader::SetFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

inline void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

inline void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

inline void Shader::SetFloatArray(const std::string& name, const std::vector<float>& values) const {
  glUniform1fv(glGetUniformLocation(id, name.c_str()), values.size(), &values[0]);
}

inline void Shader::SetVec3Array(const std::string& name, const std::vector<glm::vec3>& values) const {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), values.size(), &values[0][0]);
}

inline void Shader::SetMat4Array(const std::string& name, const std::vector<glm::mat4>& values) const {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), values.size(), GL_FALSE, &values[0][0][0]);
}

inline void Shader::CheckCompileErrors(GLuint shader, const std::string& type) const {
  GLint success;
  GLchar info_log[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, info_log);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, info_log);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}

#endif  // SHADER_H_