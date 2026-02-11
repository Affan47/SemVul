createLineString(CoordinateSequence::AutoPtr newCoords)
	const
{
	return Geometry::AutoPtr(new LineString(newCoords, this));
}
