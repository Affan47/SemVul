c_ncdid (
    int ncid,
    const char *dimname,
    int *rcode
)
{
    int dimid;

    if ((dimid = ncdimid (ncid, dimname)) == -1)
	*rcode = ncerr;
    else
    {
	dimid++;
	*rcode = 0;
    }

    return dimid;
}
