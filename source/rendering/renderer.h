#ifndef RENDERER_H
#define RENDERER_H

#include "framebuffer_manager.h"
#include "../scene/scene.h"

class Renderer {
 public:
  Renderer(FramebufferManager* framebuffer_manager);
  void RenderScene(const Scene& scene);

 private:
  FramebufferManager* framebuffer_manager_;
};

#endif  // RENDERER_H
