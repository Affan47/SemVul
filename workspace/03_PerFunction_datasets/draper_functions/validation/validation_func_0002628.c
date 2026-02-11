upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data,
		   ERL_NIF_TERM load_info)
{
    if (*old_priv_data != NULL) {
	return -1;
    }
    if (*priv_data != NULL) {
	return -1;
    }
    if (!init(env, load_info)) {
	return -1;
    }
    library_refc++;
    return 0;
}
