config_rootpw(ConfigArgs *c) {
	Backend *tbe;

	if (c->op == SLAP_CONFIG_EMIT) {
		if (!BER_BVISEMPTY(&c->be->be_rootpw)) {


			c->value_bv = c->be->be_rootpw;
			return 0;
		}
		return 1;
	} else if ( c->op == LDAP_MOD_DELETE ) {
		ch_free( c->be->be_rootpw.bv_val );
		BER_BVZERO( &c->be->be_rootpw );
		return 0;
	}

	tbe = select_backend(&c->be->be_rootndn, 0);
	if(tbe != c->be) {
		snprintf( c->cr_msg, sizeof( c->cr_msg ), "<%s> can only be set when rootdn is under suffix",
			c->argv[0] );
		Debug(LDAP_DEBUG_ANY, "%s: %s\n",
			c->log, c->cr_msg, 0);
		return(1);
	}
	if ( !BER_BVISNULL( &c->be->be_rootpw ))
		ch_free( c->be->be_rootpw.bv_val );
	c->be->be_rootpw = c->value_bv;
	return(0);
}
