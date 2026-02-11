read_coord_dimids(NC_VAR_INFO_T *var)
{
   hid_t coord_att_typeid = -1, coord_attid = -1, spaceid = -1;
   hssize_t coord_array_size;
   int ret = 0;


   if ((coord_attid = H5Aopen_name(var->hdf_datasetid, COORDINATES)) < 0) ret++;
   if (!ret && (coord_att_typeid = H5Aget_type(coord_attid)) < 0) ret++;
   if (!ret && H5Aread(coord_attid, coord_att_typeid, var->dimids) < 0) ret++;
   LOG((4, "dimscale %s is multidimensional and has coords", var->name));


   if ((spaceid = H5Aget_space(coord_attid)) < 0) ret++;
#ifdef EXTRA_TESTS
   num_spaces++;
#endif
   if ((coord_array_size = H5Sget_simple_extent_npoints(spaceid)) < 0) ret++;


   if (spaceid >= 0 && H5Sclose(spaceid) < 0) ret++;
#ifdef EXTRA_TESTS
   num_spaces--;
#endif
   if (coord_att_typeid >= 0 && H5Tclose(coord_att_typeid) < 0) ret++;
   if (coord_attid >= 0 && H5Aclose(coord_attid) < 0) ret++;
   return ret ? NC_EATTMETA : NC_NOERR;
}
