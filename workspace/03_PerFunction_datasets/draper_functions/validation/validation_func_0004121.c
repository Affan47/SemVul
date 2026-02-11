PR_Access(const char *name, PRAccessHow how)
{
    PRIntn rv;

    if (pt_TestAbort()) return PR_FAILURE;

    switch (how)
    {
    case PR_ACCESS_READ_OK:
        rv =  access(name, R_OK);
        break;
    case PR_ACCESS_WRITE_OK:
        rv = access(name, W_OK);
        break;
    case PR_ACCESS_EXISTS:
    default:
        rv = access(name, F_OK);
    }
    if (0 == rv) return PR_SUCCESS;
    pt_MapError(_PR_MD_MAP_ACCESS_ERROR, errno);
    return PR_FAILURE;

}
