HCPmstdio_inquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
 uint16 *pref, int32 *plength, int32 *poffset, int32 *pposn, int16 *paccess,
                  int16 *pspecial)
{
    CONSTR(FUNC, "HCPmstdio_inquire");
    compinfo_t *info;
    int32       ret;

    info = (compinfo_t *) access_rec->special_info;
    if ((ret = (*(info->cinfo.coder_funcs.inquire)) (access_rec, pfile_id, ptag, pref,
                       plength, poffset, pposn, paccess, pspecial)) == FAIL)
        HRETURN_ERROR(DFE_CODER, FAIL);
    return (ret);
}
