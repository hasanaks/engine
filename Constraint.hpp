#pragma once

#include <cmath>
#include <vector>
#include "Particle.hpp"

class Constraint {
public:
	Constraint(Particle* A, Vector2f* pos, float dis);
	void C2();
private:
	Vector2f* positionA{};
	Vector2f* positionB{};
	Vector2f* Va{};
	Vector2f* Vb{};
	Vector2f P{};
	Vector2f* forcext{};
	float m;
	float lambda{};
	float distance;
	float d;
	float C;
	Vector2f forceC{};
	Particle* ret{};
};
