H5S_select_elements(H5S_t *space, H5S_seloper_t op, size_t num_elem,
    const hsize_t *coord)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5S_select_elements)


    HDassert(space);
    HDassert(num_elem);
    HDassert(coord);
    HDassert(op == H5S_SELECT_SET || op == H5S_SELECT_APPEND || op == H5S_SELECT_PREPEND);


    if(op == H5S_SELECT_SET || H5S_GET_SELECT_TYPE(space) != H5S_SEL_POINTS)
        if(H5S_SELECT_RELEASE(space) < 0)
            HGOTO_ERROR(H5E_DATASPACE, H5E_CANTDELETE, FAIL, "can't release point selection")


    if(H5S_GET_SELECT_TYPE(space) != H5S_SEL_POINTS || space->select.sel_info.pnt_lst == NULL)
        if(NULL == (space->select.sel_info.pnt_lst = H5FL_CALLOC(H5S_pnt_list_t)))
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "can't allocate element information")


    if(H5S_point_add(space, op, num_elem, coord) < 0)
        HGOTO_ERROR(H5E_DATASPACE, H5E_CANTINSERT, FAIL, "can't insert elements")


    space->select.type = H5S_sel_point;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
