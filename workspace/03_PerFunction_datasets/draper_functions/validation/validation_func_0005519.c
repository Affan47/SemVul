decode_sim_MAD(Client * cl, struct sim_request * r, ib_rpc_t * rpc,
			  ib_dr_path_t * path, void *data)
{
	void *buf = r->mad;
	int response;


	response = mad_get_field(buf, 0, IB_MAD_RESPONSE_F);
	if (mad_get_field(buf, 0, IB_MAD_CLASSVER_F) > 2 ||
	    mad_get_field(buf, 0, IB_MAD_BASEVER_F) != 1) {
		IBWARN("bad smp headers (1st word)");
		return -1;
	}
	rpc->method = mad_get_field(buf, 0, IB_MAD_METHOD_F);
	rpc->mgtclass = mad_get_field(buf, 0, IB_MAD_MGMTCLASS_F);


	if (rpc->mgtclass == 0x81) {
		if (mad_get_field(buf, 0, IB_DRSMP_HOPPTR_F) != 0x0 ||
		    mad_get_field(buf, 0, IB_DRSMP_DIRECTION_F) != response) {
			IBWARN("bad direct smp headers (2nd word)");
			return -1;
		}
		path->cnt = mad_get_field(buf, 0, IB_DRSMP_HOPCNT_F);
	} else if (r->slid == 0)
		r->slid = htons(cl->port->lid);


	rpc->trid = update_trid(buf, response, cl);

	rpc->attr.id = mad_get_field(buf, 0, IB_MAD_ATTRID_F);
	rpc->attr.mod = mad_get_field(buf, 0, IB_MAD_ATTRMOD_F);


	if (rpc->mgtclass == 0x81) {

		if (mad_get_field(buf, 0, IB_DRSMP_DRDLID_F) != 0xffff ||
		    mad_get_field(buf, 0, IB_DRSMP_DRSLID_F) != 0xffff) {
			IBWARN("dr[ds]lids are used (not supported)");
			return -1;
		}

		if (!response)
			mad_get_array(buf, 0, IB_DRSMP_PATH_F, path->p);
		else
			mad_get_array(buf, 0, IB_DRSMP_RPATH_F, path->p);
	}

	if (rpc->mgtclass == 0x4 || rpc->mgtclass == 0x1
	    || rpc->mgtclass == 0x81) {
		rpc->dataoffs = 64;
		rpc->datasz = 64;
	}
	if (data)
		memcpy(data, (char *)buf + rpc->dataoffs, rpc->datasz);

	return response;
}
