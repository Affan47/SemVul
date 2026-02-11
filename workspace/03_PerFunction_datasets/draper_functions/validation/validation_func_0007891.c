H5Tget_member_offset(hid_t type_id, unsigned membno)
{
    H5T_t	*dt;
    size_t	ret_value;

    FUNC_ENTER_API(0)
    H5TRACE2("z", "iIu", type_id, membno);


    if(NULL == (dt = (H5T_t *)H5I_object_verify(type_id, H5I_DATATYPE)) || H5T_COMPOUND != dt->shared->type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, 0, "not a compound datatype")
    if(membno >= dt->shared->u.compnd.nmembs)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, 0, "invalid member number")


    ret_value = H5T_GET_MEMBER_OFFSET(dt->shared, membno);

done:
    FUNC_LEAVE_API(ret_value)
}
