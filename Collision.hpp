#pragma once


#include <vector>
#include <cmath>
#include "Eigen/Dense"
#include "Particle.hpp"

using Eigen::Vector2f;





struct AABB {
	std::shared_ptr<Particle> id;
	Vector2f min;
	Vector2f max;
};

struct debut {

	AABB* b1;
	AABB* b2;

};

struct knife_edge {
	AABB* box;
	int b;
	int mag;
};



struct CollisionPoint {
	AABB* bx1;
	AABB* bx2;
	float depth;
};


void swap(knife_edge* xp, knife_edge* yp);

void selectionSort(std::vector<knife_edge>arr, int n);

bool isOverlapping(AABB* a, AABB* b);

std::vector<knife_edge> EdgeInit(std::vector<AABB*>boxes);
void relayer(std::vector<knife_edge>elp);

