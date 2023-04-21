#include "CR.hpp"

ImpulseSolver::ImpulseSolver(std::shared_ptr<Particle> P1,
                             std::shared_ptr<Particle> P2) {
  A = P1;
  B = P2;
}

void ImpulseSolver::Imp() {
  /*Eigen::Vector4f Jacobian;
  Jacobian[0] = normal[0];			Will be useful when calculations
  of impulse is written only as matrix multiplication Jacobian[1] = normal[1];
  Jacobian[2] = -normal[0];
  Jacobian[3] = -normal[1];*/

  Vector2f relativePosition = B->position - A->position;

  Vector2f normal = relativePosition.normalized();
  float Vd = relativePosition.dot(normal);

  float invm = (1 / A->mass) + (1 / B->mass);

  float lambda = -Vd / invm;

  Vector2f aImp = normal * lambda;
  Vector2f bImp = -normal * lambda;

  A->velocity += aImp / A->mass;
  B->velocity += bImp / B->mass;
}
