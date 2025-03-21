#include "interface.h"
#include "../rendering/framebuffer_manager.h"
#include "imgui.h"

ImVec2 render_window_size;

void Interface::RenderImGui() {
  // Window header with File, Edit, View
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("New");
      ImGui::MenuItem("Open");
      ImGui::MenuItem("Save");
      ImGui::MenuItem("Exit");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      ImGui::MenuItem("Undo");
      ImGui::MenuItem("Redo");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
      ImGui::MenuItem("Show/Hide");
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  // Asset Browser
  ImGui::Begin("Asset Browser", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Preview Window
  ImGui::Begin("Preview Window", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Parameters Editor
  ImGui::Begin("Parameters Editor", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // File Browser
  ImGui::Begin("File Browser", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Render Window
  ImGui::Begin("Render Window", nullptr, ImGuiWindowFlags_NoCollapse);
  render_window_size = ImGui::GetContentRegionAvail();
  if (framebuffer_manager) {
    ImGui::Image((ImTextureID)(intptr_t)framebuffer_manager->GetTexture(), render_window_size);
  }
  ImGui::End();
}

ImVec2 Interface::GetRenderWindowSize() {
  return render_window_size;
}
