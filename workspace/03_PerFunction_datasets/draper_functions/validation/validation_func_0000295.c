gf_sg_route_set_id(GF_Route *route, u32 ID)
{
	GF_Route *ptr;
	if (!route || !ID) return GF_BAD_PARAM;

	ptr = gf_sg_route_find(route->graph, ID);
	if (ptr) return GF_BAD_PARAM;
	route->ID = ID;
	return GF_OK;
}
