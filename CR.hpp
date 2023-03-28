#pragma once

#include <cmath>
#include <vector>
#include <memory>
#include "Particle.hpp"

class ImpulseSolver {

public:
	ImpulseSolver::ImpulseSolver(std::shared_ptr<Particle> P1, std::shared_ptr<Particle> P2);
	Vector2f ImpulseSolver::normalFinder();
	void ImpulseSolver::Imp();
private:
	std::shared_ptr<Particle> A;
	std::shared_ptr<Particle> B;
};