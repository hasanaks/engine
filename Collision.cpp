#include "Collision.hpp"

AABB::AABB(PhysicsObject *physicsObject)
    : id(physicsObject),
      min(physicsObject->position - Vector2f{0, physicsObject->transform.y()}),
      max(physicsObject->position + Vector2f{physicsObject->transform.x(), 0}) {
}

bool isOverlapping(const AABB &a, const AABB &b) // helper funtion
{
  Vector2f d1 = a.min - b.max;
  Vector2f d2 = b.min - a.max;

  if (d1.x() > 0 || d1.y() > 0) {
    return false;
  }
  if (d2.x() > 0 || d2.y() > 0) {
    return false;
  }

  return true;
}

std::vector<knife_edge> EdgeInit(std::vector<AABB> boxes) {
  std::vector<knife_edge> elp;
  for (int i = 0; i < boxes.size(); i++) {
    knife_edge begin{};
    knife_edge end{};
    begin.box = boxes[i];
    begin.b = 1;
    begin.mag = begin.box.min.x();
    end.box = boxes[i];
    end.b = 0;
    end.mag = begin.box.max.x();
    elp.push_back(begin);
    elp.push_back(end);
  }

  std::sort(
      elp.begin(), elp.end(),
      [](const knife_edge &a, const knife_edge &b) { return a.mag < b.mag; });

  return elp;
} // input function

std::vector<debut> relayer(std::vector<knife_edge> elp) { // inp function
  std::vector<debut> activeList;

  if (elp.size() < 4) {
    return activeList;
  }

  int id = 0;

  while (id < elp.size() - 1) {
    if (elp[id].b != 1) {
      id++;
      continue;
    }

    knife_edge key = elp[id];

    int count = id + 1;
    knife_edge lock = elp[count];

    while (key.box.id != lock.box.id) {
      if (lock.b == 1) {
        activeList.push_back(debut{key.box, lock.box});
      }

      count++;
      if (count >= elp.size())
        break;

      lock = elp[count];
    }

    id++;
  }
  return activeList;
}

void isActive(std::vector<debut> &activeList) {
  activeList.erase(std::remove_if(activeList.begin(), activeList.end(),
                                  [](const auto &debut) {
                                    return !isOverlapping(debut.b1, debut.b2);
                                  }),
                   activeList.cend());
}
