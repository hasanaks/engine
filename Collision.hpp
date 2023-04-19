#pragma once


#include <vector>
#include <cmath>
#include "Eigen/Dense"
#include <memory>
#include "Particle.hpp"

using Eigen::Vector2f;





struct AABB {
	std::shared_ptr<Particle> id;
	Vector2f min;
	Vector2f max;
};

struct debut {

	AABB b1;
	AABB b2;

};

struct knife_edge {
	AABB box;
	int b;
	int mag;
};






void swap(knife_edge* xp, knife_edge* yp);

void selectionSort(std::vector<knife_edge>arr, int n);

bool isOverlapping(AABB* a, AABB* b);
void isActive(std::vector<debut> activeList);

std::vector<knife_edge> EdgeInit(std::vector<AABB>boxes);
std::vector<debut> relayer(std::vector<knife_edge>elp);

