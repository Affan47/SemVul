seahorse_pgp_key_get_algo (SeahorsePgpKey *self)
{
	GList *subkeys;

	g_return_val_if_fail (SEAHORSE_IS_PGP_KEY (self), 0);

	subkeys = seahorse_pgp_key_get_subkeys (self);
	if (!subkeys)
		return 0;

	return seahorse_pgp_subkey_get_algorithm (subkeys->data);
}
