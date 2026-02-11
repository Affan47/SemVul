insertPoint(int argIndex, const Coordinate& coord,
	int onLocation)
{
#if GEOS_DEBUG
	cerr<<"GeometryGraph::insertPoint("<<coord.toString()<<" called"<<endl;
#endif
	Node *n=nodes->addNode(coord);
	Label& lbl = n->getLabel();
	if ( lbl.isNull() )
	{
		n->setLabel(argIndex, onLocation);
	}
	else
	{
		lbl.setLocation(argIndex, onLocation);
	}
}
