HLPseek(accrec_t *access_rec,
        int32     offset,
        int       origin)
{
    CONSTR(FUNC, "HLPseek");
    int32   ret_value = SUCCEED;


    if (access_rec->special != SPECIAL_LINKED)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    if (origin == DF_CURRENT)
        offset += access_rec->posn;
    if (origin == DF_END)
        offset += ((linkinfo_t *) (access_rec->special_info))->length;
    if (offset < 0)
        HGOTO_ERROR(DFE_RANGE, FAIL);


    access_rec->posn = offset;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
