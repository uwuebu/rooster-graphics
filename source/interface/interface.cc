#include "interface.h"
#include "../rendering/framebuffer_manager.h"
#include "imgui.h"
#include <cstdint>

ImVec2 render_window_size;
ImVec2 preview_window_size;

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
  if (ImGui::BeginTabBar("AssetTabs")) {
    if (ImGui::BeginTabItem("Materials")) {
      // Content for Materials tab
      ImGui::Text("Materials will be listed here.");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Textures")) {
      // Content for Textures tab
      ImGui::Text("Texture assets will be listed here.");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Models")) {
      // Content for Models tab
      ImGui::Text("Model assets will be listed here.");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Scripts")) {
      // Content for Scripts tab
      ImGui::Text("Script assets will be listed here.");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Shaders")) {
      // Content for Shaders tab
      ImGui::Text("Shader assets will be listed here.");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGui::End();

  // Preview Window
  ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoCollapse);
  preview_window_size = ImGui::GetContentRegionAvail();
  if (preview_framebuffer_manager) {
    ImGui::Image((ImTextureID)(intptr_t)preview_framebuffer_manager->GetTexture(), preview_window_size);
  }
  ImGui::End();

  // Scene Hierarchy
  ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Parameters Editor
  ImGui::Begin("Parameters Editor", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Levels
  ImGui::Begin("Levels", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // File Browser
  ImGui::Begin("File Browser", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Debug
  ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Render Controls
  ImGui::Begin("Render Controls", nullptr, ImGuiWindowFlags_NoCollapse);
  // Empty for now
  ImGui::End();

  // Render Window
  ImGui::Begin("Render", nullptr, ImGuiWindowFlags_NoCollapse);
  render_window_size = ImGui::GetContentRegionAvail();
  if (framebuffer_manager) {
    ImGui::Image((ImTextureID)(intptr_t)framebuffer_manager->GetTexture(), render_window_size);
  }
  ImGui::End();
}

ImVec2 Interface::GetRenderWindowSize() {
  return render_window_size;
}

ImVec2 Interface::GetPreviewWindowSize() {
  return preview_window_size;
}

void Interface::SetPreviewFramebufferManager(FramebufferManager* manager) {
  preview_framebuffer_manager = manager;
}
