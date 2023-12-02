#include "MapPositionable.h"

MapPositionable::MapPositionable(const Coordinate &coordinate) :
	coordinate_(coordinate)
{}

const Coordinate &MapPositionable::getCoordinate() const
{
	return coordinate_;
}