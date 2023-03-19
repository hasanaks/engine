#include "Constraint.hpp"


	Constraint::Constraint(Particle* A,Vector2f* pos,float dis) {
		ret = A;
		positionA = &(A->position);
		positionB = pos;
		forcext = &(A->force);
		Va = &(A->velocity);
		P = (*positionA) - (*positionB);
		distance = pow(P.dot(P), 0.5f);
		d = dis;
		C = distance - d;
		m = A->mass;
	}
	void Constraint::C2() {
	  lambda = (-forcext->dot(*positionA)-(m*Va->dot(*Va))/(positionA->dot(*positionA)));
		forceC = (*positionA) * lambda;
		ret->force += forceC;

	}


