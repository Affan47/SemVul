NC3_inq_var(int ncid,
	int varid,
	char *name,
	nc_type *typep,
	int *ndimsp,
	int *dimids,
	int *nattsp)
{
	int status;
	NC *ncp;
	NC_var *varp;
	size_t ii;

	status = NC_check_id(ncid, &ncp);
	if(status != NC_NOERR)
		return status;

	varp = elem_NC_vararray(&ncp->vars, (size_t)varid);
	if(varp == NULL)
		return NC_ENOTVAR;

	if(name != NULL)
	{
		(void) strncpy(name, varp->name->cp, varp->name->nchars);
		name[varp->name->nchars] = 0;
	}

	if(typep != 0)
		*typep = varp->type;
	if(ndimsp != 0)
	{
		*ndimsp = (int) varp->ndims;
	}
	if(dimids != 0)
	{
		for(ii = 0; ii < varp->ndims; ii++)
		{
			dimids[ii] = varp->dimids[ii];
		}
	}
	if(nattsp != 0)
	{
		*nattsp = (int) varp->attrs.nelems;
	}

	return NC_NOERR;
}
