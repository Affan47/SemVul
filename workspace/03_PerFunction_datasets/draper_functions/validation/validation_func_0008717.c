binding_scope_get_value (omapi_value_t **value,
				      struct binding_scope *scope,
				      omapi_data_string_t *name)
{
	struct binding *bp;
	omapi_typed_data_t *td;
	isc_result_t status;
	char *nname;
	nname = dmalloc (name -> len + 1, MDL);
	if (!nname)
		return ISC_R_NOMEMORY;
	memcpy (nname, name -> value, name -> len);
	nname [name -> len] = 0;
	bp = find_binding (scope, nname);
	dfree (nname, MDL);
	if (!bp)
		return DHCP_R_UNKNOWNATTRIBUTE;
	if (!bp -> value)
		return DHCP_R_UNKNOWNATTRIBUTE;

	switch (bp -> value -> type) {
	      case binding_boolean:
		td = (omapi_typed_data_t *)0;
		status = omapi_typed_data_new (MDL, &td, omapi_datatype_int,
					       bp -> value -> value.boolean);
		break;

	      case binding_numeric:
		td = (omapi_typed_data_t *)0;
		status = omapi_typed_data_new (MDL, &td, omapi_datatype_int,
					       (int)
					       bp -> value -> value.intval);
		break;

	      case binding_data:
		td = (omapi_typed_data_t *)0;
		status = omapi_typed_data_new (MDL, &td, omapi_datatype_data,
					       bp -> value -> value.data.len);
		if (status != ISC_R_SUCCESS)
			return status;
		memcpy (&td -> u.buffer.value [0],
			bp -> value -> value.data.data,
			bp -> value -> value.data.len);
		break;


	      case binding_dns:
	      case binding_function:
		return DHCP_R_INVALIDARG;

	      default:
		log_fatal ("Impossible case at %s:%d.", MDL);
		return ISC_R_FAILURE;
	}

	if (status != ISC_R_SUCCESS)
		return status;
	status = omapi_value_new (value, MDL);
	if (status != ISC_R_SUCCESS) {
		omapi_typed_data_dereference (&td, MDL);
		return status;
	}

	omapi_data_string_reference (&(*value) -> name, name, MDL);
	omapi_typed_data_reference (&(*value) -> value, td, MDL);
	omapi_typed_data_dereference (&td, MDL);

	return ISC_R_SUCCESS;
}
