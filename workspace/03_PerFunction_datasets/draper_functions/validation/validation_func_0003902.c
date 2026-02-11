nc_put_varm (int ncid, int varid, const size_t * start,
	     const size_t * edges, const ptrdiff_t * stride,
	     const ptrdiff_t * imapp, const void *value)
{
   NC* ncp;
   int stat;

   if ((stat = NC_check_id(ncid, &ncp)))
       return stat;
   return ncp->dispatch->put_varm(ncid, varid, start, edges, stride, imapp,
		      value, NC_NAT);
}
