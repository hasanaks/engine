#include "Constraint.hpp"


	Constraint::Constraint(std::shared_ptr<Particle> A,Vector2f pos) {
		ret = A;
		positionA = &(A->position);
		positionB = pos;
		forcext = &(A->force);
		Va = &(A->velocity);
		relP = (*positionA) - (positionB);
		m = A->mass;
	}
	void Constraint::C2() {
	  lambda = (-forcext->dot(relP)-(m*Va->dot(*Va)))/relP.dot(relP);
		forceC = (relP) * lambda;
		ret->force += forceC;

	}


