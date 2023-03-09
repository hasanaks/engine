#pragma once


#include <vector>
#include "Vector.hpp"

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

void swap(knife_edge* xp, knife_edge* yp);

void selectionSort(std::vector<knife_edge>arr, int n);

bool isOverlapping(AABB* a, AABB* b);

void EdgeInit();
void relayer();
int narrowPhase(AABB* b1, AABB* b2);
