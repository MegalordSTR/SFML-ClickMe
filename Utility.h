#pragma once
#include <SFML/Graphics.hpp>

#include <chrono>
#include <random>


// Random number generation
int	randIntN(int exclusiveMax);
float randFloatN(float exclusiveMax);

// Returns float [0;1]
float randFloatNorm();


// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);