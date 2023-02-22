#include<iostream>
#include<raylib.h>
#include<vector>

struct Particle
{
	Vector2 P;
	Vector2 V;
	float m;
};

std::vector<Particle> particles;

void PrintParticles(void) {
	for  (const auto& a : particles)
	{
		std::cout << a.P.x << " x, " << a.P.y << " y.\n";
	}
}

void ParticleInit(void) {
	for (Particle& a : particles) {
		a.P.x = GetRandomValue(-50, 50);
		a.P.y = GetRandomValue(-50, 50);
		a.V = Vector2( { 0, 0 });


	}
}

Vector2 ComputeForce(Particle* particle) {
	return Vector2({ 0,particle->m * (-10.0f) });
}

void Run(void) {
	float t_total = 10;
	float t_c = 0;
	float dt = 1;
	Vector2 a_0=Vector2({0,0});
	ParticleInit();
	PrintParticles();

	while (t_c < t_total) {

		_sleep(dt);
		for (int i = 0; i < particles.size(); i++) {
			Particle* part = &particles[i];
			Vector2 Force = ComputeForce(part);
			Vector2 a = Vector2({ Force.x / part->m,Force.y / part->m });
			if (t_c == 0) { a_0 = a; }
			Vector2 a_avg = Vector2({ (a.x + a_0.x) / 2.0f,(a.y + a_0.y) / 2.0f });
			part->P.x += part->V.x * dt + (1.0f / 2.0f) * a_avg.x * dt * dt;
			part->P.y += part->V.y * dt + (1.0f / 2.0f) * a_avg.y * dt * dt;
			part->V.x += a.x * dt;
			part->V.y += a.y * dt;
		}
		PrintParticles();
		t_c += dt;
	}
}

int main() {
	Particle part;
	particles.push_back(part);
	Run();
}