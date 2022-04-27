#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_
#include "hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

private:
  std::vector<std::shared_ptr<Hittable>> objects;
};

#endif // HITTABLE_LIST_H_
