#include "window/input_handler.h"
#include "window/window.h"
#include "imgui/imgui_manager.h"
#include "interface/interface.h"
#include "rendering/framebuffer_manager.h"
#include "rendering/renderer.h"

FramebufferManager* framebuffer_manager;

// standart libraries
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

void main() {
  Window window(4, 5);
  InputHandler input_handler;
  window.SetInputHandler(&input_handler);

  ImGuiManager imgui_manager(window);
  FramebufferManager framebuffer_manager_instance(800, 600);
  framebuffer_manager = &framebuffer_manager_instance;
  Renderer renderer(framebuffer_manager);

  // RENDER LOOP
  // =--------------------------------------------------=
  while (!glfwWindowShouldClose(window.GetWindowPTR())) {
    // per-frame time logic
    // --------------------

    // Get the size of the render window
    ImVec2 render_window_size = Interface::GetRenderWindowSize();
    framebuffer_manager->Resize(render_window_size.x, render_window_size.y);

    renderer.RenderScene();

    imgui_manager.BeginFrame();

    Interface::RenderImGui();

    imgui_manager.EndFrame();

    // glfw: swap buffers and poll IO events (keys pressed/released, 
    // mouse moved etc.)
    // -----------------------------------------------------------------
    glfwSwapBuffers(window.GetWindowPTR());
    glfwPollEvents();
  }
}

