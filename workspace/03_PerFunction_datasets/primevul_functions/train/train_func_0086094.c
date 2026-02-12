ca_sslinit(void)
{
	OpenSSL_add_all_algorithms();
	ERR_load_crypto_strings();


	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();
}
