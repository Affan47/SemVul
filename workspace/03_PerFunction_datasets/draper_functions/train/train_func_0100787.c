DAsize_array(dynarr_p arr
)
{
    CONSTR(FUNC, "DAsize_array");
    dynarr_t   *arr_ptr;
    intn    ret_value=SUCCEED;

    HEclear();
    arr_ptr=(dynarr_t *)arr;
    if(arr_ptr==NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);

    ret_value=arr_ptr->num_elems;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
