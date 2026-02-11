getBoundaryDimension() const
{
	int dimension=Dimension::False;
	for(size_t i=0; i<geometries->size(); ++i) {
		dimension=max(dimension,(*geometries)[i]->getBoundaryDimension());
	}
	return dimension;
}
