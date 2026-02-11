vattr_map_namespace_sp_getlist(Slapi_DN *dn, const char *type_to_find)
{
	int ret = 0;
	vattr_map_entry *result = NULL;
	vattr_sp_handle_list* return_list = 0;

	if(config_get_ignore_vattrs()){

		return NULL;
	}

	ret = vattr_map_lookup(type_to_find,&result);
	if (0 == ret) {
		return_list = (vattr_sp_handle_list*) result->sp_list;
	} else {


		if(dn) {
			char *split_dn = (char*)slapi_sdn_get_dn(dn);
			char *split_type_to_find =
				slapi_ch_smprintf("%s::%s",split_dn, type_to_find);

			if(split_type_to_find)
			{
				ret = vattr_map_lookup(split_type_to_find,&result);
				if (0 == ret) {
					return_list = (vattr_sp_handle_list*) result->sp_list;
				}

				slapi_ch_free((void **)&split_type_to_find);
			}
		}
	}

	return return_list;
}
