#include "Collision.hpp"

AABB::AABB(PhysicsObject *physicsObject)
    : id(physicsObject),
      min(physicsObject->position - Vector2f{0, physicsObject->transform.y()}),
      max(physicsObject->position + Vector2f{physicsObject->transform.x(), 0}) {
}

bool AABB::OverlappingWith(const AABB &anotherBox) const {
  Vector2f d1 = min - anotherBox.max;
  Vector2f d2 = anotherBox.min - max;

  if (d1.x() > 0 || d1.y() > 0) {
    return false;
  }
  if (d2.x() > 0 || d2.y() > 0) {
    return false;
  }

  return true;
}

namespace {
struct SortedBox {
  AABB box;
  int b;
  int mag;
};

// returns a vector of sorted boxes of size boxes.size * 2
std::vector<SortedBox> SortBoxes(std::vector<AABB> boxes) {
  std::vector<SortedBox> sortedBoxes(boxes.size() * 2);

  for (const auto &box : boxes) {
    SortedBox begin{};
    SortedBox end{};
    begin.box = box;
    begin.b = 1;
    begin.mag = begin.box.min.x();
    end.box = box;
    end.b = 0;
    end.mag = begin.box.max.x();
    sortedBoxes.push_back(begin);
    sortedBoxes.push_back(end);
  }

  std::sort(
      sortedBoxes.begin(), sortedBoxes.end(),
      [](const auto &box1, const auto &box2) { return box1.mag < box2.mag; });

  return sortedBoxes;
}

void FilterActiveBoxes(std::vector<std::pair<AABB, AABB>> &boxPairs) {
  boxPairs.erase(std::remove_if(boxPairs.begin(), boxPairs.end(),
                                [](const auto &boxPair) {
                                  return boxPair.first.OverlappingWith(
                                      boxPair.second);
                                }),
                 boxPairs.cend());
}
} // namespace

std::vector<std::pair<AABB, AABB>>
FindOverlappingBoxes(std::vector<AABB> boxes) {
  const auto sortedBoxes = SortBoxes(boxes);
  std::vector<std::pair<AABB, AABB>> overlappingList;

  // search for overlapping boxes when there are at least 2 boxes
  if (sortedBoxes.size() <= 2) {
    return overlappingList;
  }

  auto id = 0;

  while (id < sortedBoxes.size() - 1) {
    if (sortedBoxes[id].b != 1) {
      id++;
      continue;
    }

    const auto key = sortedBoxes[id];

    auto count = id + 1;
    auto lock = sortedBoxes[count];

    while (key.box.id != lock.box.id) {
      if (lock.b == 1) {
        overlappingList.emplace_back(key.box, lock.box);
      }

      count++;
      if (count >= sortedBoxes.size())
        break;

      lock = sortedBoxes[count];
    }

    id++;
  }

  FilterActiveBoxes(overlappingList);
  return overlappingList;
}
