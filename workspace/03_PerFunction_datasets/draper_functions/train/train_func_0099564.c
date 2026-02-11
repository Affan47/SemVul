HXPseek(accrec_t * access_rec, int32 offset, int origin)
{
    int32     ret_value = SUCCEED;
    CONSTR(FUNC, "HXPseek");


    if (origin == DF_CURRENT)
        offset += access_rec->posn;
    if (origin == DF_END)
        offset += ((extinfo_t *) (access_rec->special_info))->length;
    if (offset < 0)
        HGOTO_ERROR(DFE_RANGE, FAIL);


    access_rec->posn = offset;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
