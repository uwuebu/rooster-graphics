#include "renderer.h"
#include <glad/glad.h>

Renderer::Renderer(FramebufferManager* framebuffer_manager)
    : framebuffer_manager_(framebuffer_manager) {}

void Renderer::RenderScene(const Scene& scene) {
  framebuffer_manager_->Bind();
  
  // Clear the framebuffer
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render objects
  for (const auto& object : scene.GetObjects()) {
    // Render object
    // ...
  }

  // Render models
  for (const auto& model : scene.GetModels()) {
    // Render model
    // ...
  }

  // Render meshes
  for (const auto& mesh : scene.GetMeshes()) {
    // Render mesh
    // ...
  }

  framebuffer_manager_->Unbind();
}
