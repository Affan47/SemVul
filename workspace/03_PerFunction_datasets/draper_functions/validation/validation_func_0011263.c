H5S_point_offset(const H5S_t *space, hsize_t *offset)
{
    const hsize_t *pnt;
    const hssize_t *sel_offset;
    const hsize_t *dim_size;
    hsize_t accum;
    int i;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(space);
    HDassert(offset);


    *offset = 0;


    pnt = space->select.sel_info.pnt_lst->head->pnt;
    sel_offset = space->select.offset;
    dim_size = space->extent.size;


    accum = 1;
    for(i = (int)space->extent.rank - 1; i >= 0; i--) {
        hssize_t pnt_offset = (hssize_t)pnt[i] + sel_offset[i];


        if(pnt_offset < 0 || (hsize_t)pnt_offset >= dim_size[i])
            HGOTO_ERROR(H5E_DATASPACE, H5E_BADRANGE, FAIL, "offset moves selection out of bounds")


        *offset += (hsize_t)pnt_offset * accum;


        accum *= dim_size[i];
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
