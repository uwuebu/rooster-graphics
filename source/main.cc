#include "window/input_handler.h"
#include "window/window.h"
#include "imgui/imgui_manager.h"
#include "interface/interface.h"
#include "rendering/framebuffer_manager.h"
#include "rendering/renderer.h"
#include "scene/scene.h"

FramebufferManager* framebuffer_manager;
FramebufferManager* preview_framebuffer_manager;

// standart libraries
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
#include <memory>

int main() {
  Window window(4, 5);
  InputHandler input_handler;
  window.SetInputHandler(&input_handler);

  ImGuiManager imgui_manager(window);

  // scene framebuffer manager
  FramebufferManager framebuffer_manager_instance(800, 600);
  framebuffer_manager = &framebuffer_manager_instance;
  
  // preview framebuffer manager
  FramebufferManager preview_framebuffer_manager_instance(800, 600);
  preview_framebuffer_manager = &preview_framebuffer_manager_instance;
  Interface::SetPreviewFramebufferManager(preview_framebuffer_manager);
  
  // Create scene
  Scene scene;
  // Add objects, models, and meshes to the scene
  // scene.AddObject(std::make_shared<DerivedObject>(...));
  // scene.AddModel(...);
  // scene.AddMesh(...);

  // Creating renderers
  Renderer scene_renderer(framebuffer_manager);
  Renderer preview_renderer(preview_framebuffer_manager);

  // RENDER LOOP
  // =--------------------------------------------------=
  while (!glfwWindowShouldClose(window.GetWindowPTR())) {
    // Process input
    input_handler.ProcessInput(window.GetWindowPTR());

    // Get the size of the render window
    ImVec2 render_window_size = Interface::GetRenderWindowSize();
    framebuffer_manager->Resize(render_window_size.x, render_window_size.y);

    // Get the size of the preview window
    ImVec2 preview_window_size = Interface::GetPreviewWindowSize();
    preview_framebuffer_manager->Resize(preview_window_size.x, preview_window_size.y);

    scene_renderer.RenderScene(scene);
    preview_renderer.RenderScene(scene);

    imgui_manager.BeginFrame(); // Ensure ImGui frame begins

    if (input_handler.ShouldRenderImGui()) {
      Interface::RenderImGui();
    } else {
      // Render the main framebuffer full screen
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      ImVec2 window_size = window.GetWindowSize();
      ImGui::Begin("FullScreen", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
      ImGui::SetWindowPos(ImVec2(0, 0));
      ImGui::SetWindowSize(window_size);
      ImGui::Image((ImTextureID)(intptr_t)framebuffer_manager->GetTexture(), window_size);
      ImGui::End();
    }

    imgui_manager.EndFrame(); // Ensure ImGui frame ends

    glfwSwapBuffers(window.GetWindowPTR());
    glfwPollEvents();
  }

  return 0;
}

