#ifndef SCENE_H
#define SCENE_H

#include "../rendering/framebuffer_manager.h"
#include "../object/object.h"
#include "../object/model.h"
#include "../object/mesh.h"
#include <vector>
#include <memory>

class Scene {
 public:
  Scene();
  ~Scene();

  void AddObject(std::shared_ptr<Object> object);
  void AddModel(const Model& model);
  void AddMesh(const Mesh& mesh);

  const std::vector<std::shared_ptr<Object>>& GetObjects() const;
  const std::vector<Model>& GetModels() const;
  const std::vector<Mesh>& GetMeshes() const;

 private:
  std::vector<std::shared_ptr<Object>> objects_;
  std::vector<Model> models_;
  std::vector<Mesh> meshes_;
};

#endif  // SCENE_H
