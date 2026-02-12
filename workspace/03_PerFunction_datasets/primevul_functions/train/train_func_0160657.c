dnX509normalize( void *x509_name, struct berval *out )
{

	int rc = ldap_X509dn2bv( x509_name, out, LDAPDN_rewrite, 0 );

	Debug( LDAP_DEBUG_TRACE,
		"dnX509Normalize: <%s> (%d)\n",
		BER_BVISNULL( out ) ? "(null)" : out->bv_val, rc, 0 );

	return rc;
}
