certificateValidate( Syntax *syntax, struct berval *in )
{
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_tag_t tag;
	ber_len_t len;
	ber_int_t version = SLAP_X509_V1;

	ber_init2( ber, in, LBER_USE_DER );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	tag = ber_peek_tag( ber, &len );

	if ( tag == SLAP_X509_OPT_C_VERSION ) {
		tag = ber_skip_tag( ber, &len );
		tag = ber_get_int( ber, &version );
		if ( tag != LBER_INTEGER ) return LDAP_INVALID_SYNTAX;
	}


	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_INTEGER ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );
	if ( tag == SLAP_X509_OPT_C_ISSUERUNIQUEID ) {
		if ( version < SLAP_X509_V2 ) return LDAP_INVALID_SYNTAX;
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );
	}
	if ( tag == SLAP_X509_OPT_C_SUBJECTUNIQUEID ) {
		if ( version < SLAP_X509_V2 ) return LDAP_INVALID_SYNTAX;
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );
	}
	if ( tag == SLAP_X509_OPT_C_EXTENSIONS ) {
		if ( version < SLAP_X509_V3 ) return LDAP_INVALID_SYNTAX;
		tag = ber_skip_tag( ber, &len );
		if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );
	}

	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );

	if ( tag != LBER_BITSTRING ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );
	tag = ber_skip_tag( ber, &len );

	if ( len || tag != LBER_DEFAULT ) return LDAP_INVALID_SYNTAX;
	return LDAP_SUCCESS;
}
