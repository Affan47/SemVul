struct cred *prepare_exec_creds(void)
{
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return new;

#ifdef CONFIG_KEYS

	key_put(new->thread_keyring);
	new->thread_keyring = NULL;


	key_put(new->process_keyring);
	new->process_keyring = NULL;
#endif

	return new;
}
