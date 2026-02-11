createNode(const geom::Coordinate &coord) const
{
	return new Node(coord, new DirectedEdgeStar());
}
