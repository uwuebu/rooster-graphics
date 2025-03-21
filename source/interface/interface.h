#ifndef INTERFACE_H
#define INTERFACE_H

#include "../rendering/framebuffer_manager.h"
#include "imgui.h"  // Include ImGui header for ImVec2

class Interface {
 public:
  static void RenderImGui();
  static ImVec2 GetRenderWindowSize();
};

extern FramebufferManager* framebuffer_manager;

#endif  // INTERFACE_H
