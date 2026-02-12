attributeCertificateValidate( Syntax *syntax, struct berval *in )
{
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_tag_t tag;
	ber_len_t len;
	ber_int_t version;
	int cont = 0;

	ber_init2( ber, in, LBER_USE_DER );

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;

	tag = ber_peek_tag( ber, &len );
	if ( tag != LBER_INTEGER ) return LDAP_INVALID_SYNTAX;
	tag = ber_get_int( ber, &version );
	if ( version != SLAP_X509AC_V2 ) return LDAP_INVALID_SYNTAX;

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_skip_tag( ber, &len );
	if ( tag != SLAP_X509AC_ISSUER ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_INTEGER ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	ber_skip_data( ber, len );

	tag = ber_peek_tag( ber, &len );

	if ( tag == LBER_BITSTRING ) {
		tag = ber_skip_tag( ber, &len );
		ber_skip_data( ber, len );
		tag = ber_peek_tag( ber, &len );
	}

	if ( tag == LBER_SEQUENCE ) {
		tag = ber_skip_tag( ber, &len );
		ber_skip_data( ber, len );
		cont++;
		tag = ber_peek_tag( ber, &len );
	}

	if ( tag == LBER_SEQUENCE ) {
		tag = ber_skip_tag( ber, &len );
		ber_skip_data( ber, len );
		cont++;
		tag = ber_peek_tag( ber, &len );
	}

	if ( tag == LBER_BITSTRING ) {
		tag = ber_skip_tag( ber, &len );
		ber_skip_data( ber, len );
		cont++;
		tag = ber_peek_tag( ber, &len );
	}


	if ( len != 0 || tag != LBER_DEFAULT || cont < 2 ) return LDAP_INVALID_SYNTAX;

	return LDAP_SUCCESS;
}
