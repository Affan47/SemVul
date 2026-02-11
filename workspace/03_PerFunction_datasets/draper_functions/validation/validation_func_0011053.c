NC_put_var(int ncid, int varid, const void *value, nc_type memtype)
{
   int ndims;
   size_t shape[NC_MAX_VAR_DIMS];
   int stat = nc_inq_varndims(ncid,varid, &ndims);
   if(stat) return stat;
   stat = getshape(ncid,varid, ndims, shape);
   if(stat) return stat;
   return NC_put_vara(ncid, varid, coord_zero, shape, value, memtype);
}
