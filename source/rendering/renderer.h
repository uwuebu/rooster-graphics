#ifndef RENDERER_H
#define RENDERER_H

#include "framebuffer_manager.h"

class Renderer {
 public:
  Renderer(FramebufferManager* framebuffer_manager);
  void RenderScene();

 private:
  FramebufferManager* framebuffer_manager_;
};

#endif  // RENDERER_H
