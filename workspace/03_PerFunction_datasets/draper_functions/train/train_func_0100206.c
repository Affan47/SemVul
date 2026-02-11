ldap_back_init_cf( BackendInfo *bi )
{
	int			rc;
	AttributeDescription	*ad = NULL;
	const char		*text;


	config_check_userland( LDAP_BACK_CFG_LAST );

	bi->bi_cf_ocs = ldapocs;

	rc = config_register_schema( ldapcfg, ldapocs );
	if ( rc ) {
		return rc;
	}


	rc = slap_str2ad( "olcDbACLPasswd", &ad, &text );
	if ( rc ) {
		Debug( LDAP_DEBUG_ANY, "config_back_initialize: "
			"warning, unable to get \"olcDbACLPasswd\" "
			"attribute description: %d: %s\n",
			rc, text, 0 );
	} else {
		(void)ldif_must_b64_encode_register( ad->ad_cname.bv_val,
			ad->ad_type->sat_oid );
	}

	ad = NULL;
	rc = slap_str2ad( "olcDbIDAssertPasswd", &ad, &text );
	if ( rc ) {
		Debug( LDAP_DEBUG_ANY, "config_back_initialize: "
			"warning, unable to get \"olcDbIDAssertPasswd\" "
			"attribute description: %d: %s\n",
			rc, text, 0 );
	} else {
		(void)ldif_must_b64_encode_register( ad->ad_cname.bv_val,
			ad->ad_type->sat_oid );
	}

	return 0;
}
