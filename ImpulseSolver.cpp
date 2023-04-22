#include "ImpulseSolver.hpp"

ImpulseSolver::ImpulseSolver(PhysicsObject *physicsObject1,
                             PhysicsObject *physicsObject2)
    : physicsObject1(physicsObject1), physicsObject2(physicsObject2) {}

void ImpulseSolver::Imp() {
  /*Eigen::Vector4f Jacobian;
  Jacobian[0] = normal[0];			Will be useful when calculations
  of impulse is written only as matrix multiplication Jacobian[1] = normal[1];
  Jacobian[2] = -normal[0];
  Jacobian[3] = -normal[1];*/

  Vector2f relativePosition =
      physicsObject2->position - physicsObject1->position;

  Vector2f normal = relativePosition.normalized();
  float Vd = relativePosition.dot(normal);

  float invm = (1 / physicsObject1->mass) + (1 / physicsObject2->mass);

  float lambda = -Vd / invm;

  Vector2f aImp = normal * lambda;
  Vector2f bImp = -normal * lambda;

  physicsObject1->velocity += aImp / physicsObject1->mass;
  physicsObject2->velocity += bImp / physicsObject2->mass;
}
