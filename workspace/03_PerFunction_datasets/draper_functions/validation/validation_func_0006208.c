ldns_key_new_frm_engine(ldns_key **key, ENGINE *e, char *key_id, ldns_algorithm alg)
{
	ldns_key *k;

	k = ldns_key_new();
        if(!k) return LDNS_STATUS_MEM_ERR;
#ifndef S_SPLINT_S
	k->_key.key = ENGINE_load_private_key(e, key_id, UI_OpenSSL(), NULL);
        if(!k->_key.key) {
                ldns_key_free(k);
                return LDNS_STATUS_ERR;
        }
	ldns_key_set_algorithm(k, (ldns_signing_algorithm) alg);
	if (!k->_key.key) {
                ldns_key_free(k);
		return LDNS_STATUS_ENGINE_KEY_NOT_LOADED;
	}
#endif
	*key = k;
	return LDNS_STATUS_OK;
}
