oidm_destroy()
{
	OidMacro *om;
	while( !LDAP_STAILQ_EMPTY( &om_list )) {
		om = LDAP_STAILQ_FIRST( &om_list );
		LDAP_STAILQ_REMOVE_HEAD( &om_list, som_next );

		ber_bvarray_free(om->som_names);
		ber_bvarray_free(om->som_subs);
		free(om->som_oid.bv_val);
		free(om);

	}
}
