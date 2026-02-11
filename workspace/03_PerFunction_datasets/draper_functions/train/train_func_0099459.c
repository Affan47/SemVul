getLocation(int geomIndex,
	const Coordinate& p, std::vector<GeometryGraph*> *geom)
{

	if (ptInAreaLocation[geomIndex]==Location::UNDEF)
	{
		ptInAreaLocation[geomIndex]=algorithm::locate::SimplePointInAreaLocator::locate(p,
				(*geom)[geomIndex]->getGeometry());
	}
	return ptInAreaLocation[geomIndex];
}
