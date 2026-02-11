private_key_belongs_to(private_key_t *private, public_key_t *public)
{
	cred_encoding_type_t type;
	chunk_t a, b;

	for (type = 0; type < CRED_ENCODING_MAX; type++)
	{
		if (private->get_fingerprint(private, type, &a) &&
			public->get_fingerprint(public, type, &b))
		{
			return chunk_equals(a, b);
		}
	}
	return FALSE;
}
