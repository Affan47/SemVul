c_ncvinq (
    int ncid,
    int varid,
    char* varname,
    nc_type* datatype,
    int* indims,
    int* dimarray,
    int* inatts,
    int* rcode
)
{
    *rcode = ncvarinq(ncid, varid, varname, datatype, indims,
		      dimarray, inatts) == -1
		? ncerr
		: 0;
}
