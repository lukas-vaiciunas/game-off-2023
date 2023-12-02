#pragma once

#include <random>

class Random
{
public:
	Random(const Random &) = delete;
	Random(Random &&) = delete;

	Random &operator=(const Random &) = delete;
	Random &operator=(Random &&) = delete;

	static Random &getInstance();

	std::mt19937 &getEngine();
private:
	std::mt19937 engine_;

	Random();
	~Random() = default;
};