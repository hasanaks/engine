#pragma once


#include <vector>
#include <cmath>
#include "Eigen/Dense"

using Eigen::Vector2f;

struct AABB {
	Vector2f min;
	Vector2f max;
};


struct knife_edge {
	AABB* box;
	int b;
	int mag;
};

struct debut {

	AABB* b1;
	AABB* b2;

};

struct CollisionPoint {
	AABB* bx1;
	AABB* bx2;
	float depth;
};


void swap(knife_edge* xp, knife_edge* yp);

void selectionSort(std::vector<knife_edge>arr, int n);

bool isOverlapping(AABB* a, AABB* b);

void EdgeInit();
void relayer();
int narrowPhase(AABB* b1, AABB* b2);
