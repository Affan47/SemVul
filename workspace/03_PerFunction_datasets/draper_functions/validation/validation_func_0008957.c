test_der_private (gcry_sexp_t key)
{
	GBytes *data;
	GkmDataResult ret;
	gcry_sexp_t sexp;


	data = gkm_data_der_write_private_key (key);
	g_assert ("couldn't encode private key" && data != NULL);
	g_assert ("encoding is empty" && g_bytes_get_size (data) > 0);


	ret = gkm_data_der_read_private_key (data, &sexp);
	g_assert ("couldn't decode private key" && ret == GKM_DATA_SUCCESS);
	g_assert ("parsed key is empty" && sexp != NULL);


	g_assert ("key parsed differently" && compare_keys (key, sexp));

	g_bytes_unref (data);
}
