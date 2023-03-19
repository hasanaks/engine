#include "Constraint.hpp"


	Constraint::Constraint(Particle* A,Vector2f* pos,float dis) {
		ret = A;
		positionA = &(A->position);
		positionB = pos;
		forcext = &(A->force);
		Va = &(A->velocity);
		P = (*positionA) - (*positionB);
		distance = pow(P * P, 1 / 2);
		d = dis;
		C = distance - d;
		m = A->mass;
	}
	void Constraint::C2() {
		lambda = (-1*(*forcext) * (*positionA)-(m*(*Va)*(*Va)))/((*positionA)*(*positionA));
		forceC = (*positionA) * lambda;
		ret->force += forceC;

	}


