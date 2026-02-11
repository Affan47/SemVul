add_builtin(gssapi_mech_interface mech)
{
    struct _gss_mech_switch *m;
    OM_uint32 minor_status;


    if (mech == NULL)
	return 0;

    m = calloc(1, sizeof(*m));
    if (m == NULL)
	return ENOMEM;
    m->gm_so = NULL;
    m->gm_mech = *mech;
    m->gm_mech_oid = mech->gm_mech_oid;
    gss_add_oid_set_member(&minor_status,
			   &m->gm_mech.gm_mech_oid, &_gss_mech_oids);


    if (m->gm_mech.gm_inquire_names_for_mech)
	(*m->gm_mech.gm_inquire_names_for_mech)(&minor_status,
	    &m->gm_mech.gm_mech_oid, &m->gm_name_types);

    if (m->gm_name_types == NULL)
	gss_create_empty_oid_set(&minor_status, &m->gm_name_types);

    HEIM_SLIST_INSERT_HEAD(&_gss_mechs, m, gm_link);
    return 0;
}
