#ifndef FRAMEBUFFER_MANAGER_H
#define FRAMEBUFFER_MANAGER_H

class FramebufferManager {
 public:
  FramebufferManager(int width, int height);
  ~FramebufferManager();
  void Bind();
  void Unbind();
  void Resize(int width, int height);
  unsigned int GetTexture() const;

 private:
  void Initialize(int width, int height);

  unsigned int framebuffer_;
  unsigned int texture_;
  unsigned int renderbuffer_;
};

#endif  // FRAMEBUFFER_MANAGER_H
