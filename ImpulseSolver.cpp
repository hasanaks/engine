#include "ImpulseSolver.hpp"

ImpulseSolver::ImpulseSolver(std::shared_ptr<PhysicsObject> particle1,
                             std::shared_ptr<PhysicsObject> particle2)
    : particle1(particle1), particle2(particle2) {}

void ImpulseSolver::Imp() {
  /*Eigen::Vector4f Jacobian;
  Jacobian[0] = normal[0];			Will be useful when calculations
  of impulse is written only as matrix multiplication Jacobian[1] = normal[1];
  Jacobian[2] = -normal[0];
  Jacobian[3] = -normal[1];*/

  Vector2f relativePosition = particle2->position - particle1->position;

  Vector2f normal = relativePosition.normalized();
  float Vd = relativePosition.dot(normal);

  float invm = (1 / particle1->mass) + (1 / particle2->mass);

  float lambda = -Vd / invm;

  Vector2f aImp = normal * lambda;
  Vector2f bImp = -normal * lambda;

  particle1->velocity += aImp / particle1->mass;
  particle2->velocity += bImp / particle2->mass;
}
