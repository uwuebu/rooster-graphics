#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class InputHandler {
 public:
  InputHandler() : f5_pressed_(false), render_imgui_(true) {}
  void ProcessInput(GLFWwindow* window);
  bool IsF5Pressed() const;
  bool ShouldRenderImGui() const;

 private:
  bool f5_pressed_;
  bool render_imgui_;
};

#endif  // INPUTHANDLER_H_