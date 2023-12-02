#pragma once

#include "Coordinate.h"

class MapPositionable
{
public:
	MapPositionable(const Coordinate &coordinate);

	virtual ~MapPositionable() = default;

	const Coordinate &getCoordinate() const;
protected:
	Coordinate coordinate_;
};