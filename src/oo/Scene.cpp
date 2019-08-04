#include "Scene.h"

using oo::Primitive;
using oo::Scene;

bool Scene::intersect(const Ray &ray, IntersectionRecord &intersection) const {
  Primitive::IntersectionRecord *currentNearest{};
  IntersectionRecord rec;
  for (auto &primitive : primitives_) {
    if (!primitive->intersect(ray, rec))
      continue;
    if (!currentNearest || rec.hit.distance < currentNearest->hit.distance) {
      currentNearest = &rec;
    }
  }
  if (!currentNearest)
    return false;
  intersection = *currentNearest;
  return true;
}

void Scene::add(std::unique_ptr<Primitive> primitive) {
  primitives_.emplace_back(std::move(primitive));
}

Vec3 Scene::environment(const Ray &) const { return environment_; }
