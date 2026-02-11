HCIcnbit_staccess(accrec_t * access_rec, int16 acc_mode)
{
    CONSTR(FUNC, "HCIcnbit_staccess");
    compinfo_t *info;

    info = (compinfo_t *) access_rec->special_info;

#ifdef TESTING
    printf("HCIcnbit_staccess(): info=%p, ref=%d\n", info, (int) info->comp_ref);
#endif
    if (acc_mode == DFACC_READ)
        info->aid = Hstartbitread(access_rec->file_id, DFTAG_COMPRESSED,
                                  info->comp_ref);
    else
        info->aid = Hstartbitwrite(access_rec->file_id, DFTAG_COMPRESSED,
                                   info->comp_ref, info->length);

    if (info->aid == FAIL)
        HRETURN_ERROR(DFE_DENIED, FAIL);
    if ((acc_mode&DFACC_WRITE) && Hbitappendable(info->aid) == FAIL)
        HRETURN_ERROR(DFE_DENIED, FAIL);
#ifdef TESTING
    printf("HCIcnbit_staccess(): info->aid=%d, coder_func.write=%p\n", info->aid, info->cinfo.coder_funcs.write);
#endif
    return (HCIcnbit_init(access_rec));
}
