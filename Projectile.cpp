// Projectile.cpp

#include "Projectile.h"

// Constructor: definición
Projectile::Projectile(Mesh& mesh, glm::vec3 startPosition, glm::vec3 direction, float speed)
    : mesh(mesh), position(startPosition), direction(glm::normalize(direction)), speed(speed), lifeTime(5.0f) // Vida de 5 segundos
{
}

// Método Update: definición
void Projectile::Update(float deltaTime)
{
    // Actualizar la posición del proyectil
    position += direction * speed * deltaTime;

    // Reducir el tiempo de vida
    lifeTime -= deltaTime;
}

// Método Draw: definición
void Projectile::Draw(Shader& shader, Camera& camera)
{
    // Actualizar la posición de la malla
    mesh.Position = position;

    // Dibujar el proyectil
    mesh.Draw(shader, camera);
}

// Método IsAlive: definición
bool Projectile::IsAlive() const
{
    return lifeTime > 0.0f;
}