findcsn_cb( Operation *op, SlapReply *rs )
{
	slap_callback *sc = op->o_callback;


	if ( rs->sr_err == LDAP_ADMINLIMIT_EXCEEDED ||
		(rs->sr_type == REP_SEARCH && rs->sr_err == LDAP_SUCCESS )) {
		sc->sc_private = (void *)1;
	}
	return LDAP_SUCCESS;
}
