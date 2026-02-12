int sctp_auth_set_key(struct sctp_endpoint *ep,
		      struct sctp_association *asoc,
		      struct sctp_authkey *auth_key)
{
	struct sctp_shared_key *cur_key = NULL;
	struct sctp_auth_bytes *key;
	struct list_head *sh_keys;
	int replace = 0;


	if (asoc)
		sh_keys = &asoc->endpoint_shared_keys;
	else
		sh_keys = &ep->endpoint_shared_keys;

	key_for_each(cur_key, sh_keys) {
		if (cur_key->key_id == auth_key->sca_keynumber) {
			replace = 1;
			break;
		}
	}


	if (!replace) {
		cur_key = sctp_auth_shkey_create(auth_key->sca_keynumber,
						 GFP_KERNEL);
		if (!cur_key)
			return -ENOMEM;
	}


	key = sctp_auth_create_key(auth_key->sca_keylength, GFP_KERNEL);
	if (!key)
		goto nomem;

	memcpy(key->data, &auth_key->sca_key[0], auth_key->sca_keylength);


	if (replace)
		sctp_auth_key_put(cur_key->key);
	else
		list_add(&cur_key->key_list, sh_keys);

	cur_key->key = key;
	sctp_auth_key_hold(key);

	return 0;
nomem:
	if (!replace)
		sctp_auth_shkey_free(cur_key);

	return -ENOMEM;
}
