#include "input_handler.h"
#include <GLFW/glfw3.h>

void InputHandler::ProcessInput(GLFWwindow* window) {
  static bool f5_pressed_last_frame = false;
  bool f5_currently_pressed = glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS;

  if (f5_currently_pressed && !f5_pressed_last_frame) {
    render_imgui_ = !render_imgui_;
  }

  f5_pressed_last_frame = f5_currently_pressed;
  f5_pressed_ = f5_currently_pressed;
}

bool InputHandler::IsF5Pressed() const {
  return f5_pressed_;
}

bool InputHandler::ShouldRenderImGui() const {
  return render_imgui_;
}
