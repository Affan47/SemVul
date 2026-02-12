long keyctl_negate_key(key_serial_t id, unsigned timeout, key_serial_t ringid)
{
	const struct cred *cred = current_cred();
	struct request_key_auth *rka;
	struct key *instkey, *dest_keyring;
	long ret;

	kenter("%d,%u,%d", id, timeout, ringid);


	ret = -EPERM;
	instkey = cred->request_key_auth;
	if (!instkey)
		goto error;

	rka = instkey->payload.data;
	if (rka->target_key->serial != id)
		goto error;


	ret = get_instantiation_keyring(ringid, rka, &dest_keyring);
	if (ret < 0)
		goto error;


	ret = key_negate_and_link(rka->target_key, timeout,
				  dest_keyring, instkey);

	key_put(dest_keyring);


	if (ret == 0)
		keyctl_change_reqkey_auth(NULL);

error:
	return ret;

}
