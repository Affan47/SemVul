gss_inquire_cred_by_oid(OM_uint32 *minor_status,
	                const gss_cred_id_t cred_handle,
	                const gss_OID desired_object,
	                gss_buffer_set_t *data_set)
{
    gss_union_cred_t	union_cred;
    gss_mechanism	mech;
    int			i;
    gss_buffer_set_t	union_set = GSS_C_NO_BUFFER_SET;
    gss_buffer_set_t	ret_set = GSS_C_NO_BUFFER_SET;
    OM_uint32		status, minor;

    if (minor_status == NULL)
	return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (cred_handle == GSS_C_NO_CREDENTIAL)
	return GSS_S_CALL_INACCESSIBLE_READ | GSS_S_NO_CRED;

    *minor_status = 0;
    *data_set = GSS_C_NO_BUFFER_SET;

    union_cred = (gss_union_cred_t) cred_handle;

    status = gss_create_empty_buffer_set(minor_status, &ret_set);
    if (status != GSS_S_COMPLETE) {
	return status;
    }

    status = GSS_S_UNAVAILABLE;

    for (i = 0; i < union_cred->count; i++) {
	mech = gssint_get_mechanism(&union_cred->mechs_array[i]);
	if (mech == NULL) {
	    status = GSS_S_BAD_MECH;
	    break;
	}

	if (mech->gss_inquire_cred_by_oid == NULL) {
	    status = GSS_S_UNAVAILABLE;
	    continue;
	}

	status = (mech->gss_inquire_cred_by_oid)(minor_status,
						 union_cred->cred_array[i],
						 desired_object,
						 &ret_set);
	if (status != GSS_S_COMPLETE) {
	    map_error(minor_status, mech);
	    continue;
	}

	if (union_cred->count == 1) {
	    union_set = ret_set;
	    break;
	}

	status = append_to_buffer_set(minor_status, &union_set, ret_set);
	gss_release_buffer_set(&minor, &ret_set);
	if (status != GSS_S_COMPLETE)
	    break;
    }

    if (status != GSS_S_COMPLETE)
	gss_release_buffer_set(&minor, &union_set);

    *data_set = union_set;

    return status;
}
