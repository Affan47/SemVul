H5I_iterate(H5I_type_t type, H5I_search_func_t func, void *udata, hbool_t app_ref)
{
    H5I_id_type_t *type_ptr;
    herr_t	   ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(type <= H5I_BADID || type >= H5I_next_type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, FAIL, "invalid type number")
    type_ptr = H5I_id_type_list_g[type];


    if(type_ptr && type_ptr->count > 0 && type_ptr->ids > 0) {
        unsigned u;


        for(u = 0; u < type_ptr->cls->hash_size; u++) {
            H5I_id_info_t	*id_ptr;

            id_ptr = type_ptr->id_list[u];
            while(id_ptr) {
                H5I_id_info_t	*next_id;


                next_id = id_ptr->next;
                if((!app_ref) || (id_ptr->app_count > 0)) {
                    herr_t cb_ret_val;


		    cb_ret_val = (*func)((void *)id_ptr->obj_ptr, id_ptr->id, udata);
		    if(cb_ret_val > 0)
                        HGOTO_DONE(SUCCEED)
		    else if(cb_ret_val < 0)
			HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, FAIL, "func failed")
		}
                id_ptr = next_id;
            }
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
