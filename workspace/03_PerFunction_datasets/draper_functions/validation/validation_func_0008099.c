NC3_inq_dimid(int ncid, const char *name, int *dimid_ptr)
{
        int status;
        NC *ncp;
        int dimid;

        status = NC_check_id(ncid, &ncp);
        if(status != NC_NOERR)
                return status;

        dimid = NC_finddim(&ncp->dims, name, NULL);

        if(dimid == -1)
                return NC_EBADDIM;

        if (dimid_ptr)
           *dimid_ptr = dimid;
        return NC_NOERR;
}
