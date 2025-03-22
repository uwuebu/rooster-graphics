#include "scene.h"

Scene::Scene() {
  // Initialization code if needed
}

Scene::~Scene() {
  // Cleanup code if needed
}

void Scene::AddObject(std::shared_ptr<Object> object) {
  objects_.push_back(object);
}

void Scene::AddModel(const Model& model) {
  models_.push_back(model);
}

void Scene::AddMesh(const Mesh& mesh) {
  meshes_.push_back(mesh);
}

const std::vector<std::shared_ptr<Object>>& Scene::GetObjects() const {
  return objects_;
}

const std::vector<Model>& Scene::GetModels() const {
  return models_;
}

const std::vector<Mesh>& Scene::GetMeshes() const {
  return meshes_;
}
