operator<< (std::ostream&os, const Edge& e)
{
	os << "edge";
	if ( e.name != "" ) os << " " << e.name;

	os
	   << "  LINESTRING"
	   << *(e.pts)
	   << "  " << e.label
	   << "  " << e.depthDelta
	   ;

	return os;
}
