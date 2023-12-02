#include "Random.h"

Random::Random() :
	engine_(std::random_device()())
{}

Random &Random::getInstance()
{
	static Random instance;
	return instance;
}

std::mt19937 &Random::getEngine()
{
	return engine_;
}