#ifndef PERSONAL_GRAPHICS_ENGINE_REWORKED_SOURCE_IMGUI_MANAGER_H_
#define PERSONAL_GRAPHICS_ENGINE_REWORKED_SOURCE_IMGUI_MANAGER_H_

#include "../window/window.h"

class ImGuiManager {
 public:
  explicit ImGuiManager(Window& window);
  ~ImGuiManager();
  void BeginFrame();
  void EndFrame();

 private:
  Window& window_;
};

#endif  // PERSONAL_GRAPHICS_ENGINE_REWORKED_SOURCE_IMGUI_MANAGER_H_
