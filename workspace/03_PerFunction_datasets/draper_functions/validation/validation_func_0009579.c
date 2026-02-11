main (int argc, char **argv)
{
#if !GLIB_CHECK_VERSION(2,35,0)
	g_type_init ();
#endif
	g_test_init (&argc, &argv, NULL);

	g_test_add ("/gkm/data-der/der_rsa_public", Test, NULL, setup, test_der_rsa_public, teardown);
	g_test_add ("/gkm/data-der/der_dsa_public", Test, NULL, setup, test_der_dsa_public, teardown);
	g_test_add ("/gkm/data-der/der_rsa_private", Test, NULL, setup, test_der_rsa_private, teardown);
	g_test_add ("/gkm/data-der/der_dsa_private", Test, NULL, setup, test_der_dsa_private, teardown);
	g_test_add ("/gkm/data-der/der_dsa_private_parts", Test, NULL, setup, test_der_dsa_private_parts, teardown);
	g_test_add ("/gkm/data-der/read_public_key_info", Test, NULL, setup, test_read_public_key_info, teardown);
	g_test_add ("/gkm/data-der/read_certificate", Test, NULL, setup, test_read_certificate, teardown);
	g_test_add ("/gkm/data-der/write_certificate", Test, NULL, setup, test_write_certificate, teardown);
	g_test_add ("/gkm/data-der/read_ca_certificates_public_key_info", Test, NULL, setup, test_read_ca_certificates_public_key_info, teardown);
	g_test_add ("/gkm/data-der/read_basic_constraints", Test, NULL, setup, test_read_basic_constraints, teardown);
	g_test_add ("/gkm/data-der/read_key_usage", Test, NULL, setup, test_read_key_usage, teardown);
	g_test_add ("/gkm/data-der/read_enhanced_usage", Test, NULL, setup, test_read_enhanced_usage, teardown);
	g_test_add ("/gkm/data-der/read_all_pkcs8", Test, NULL, setup, test_read_all_pkcs8, teardown);
	g_test_add ("/gkm/data-der/read_pkcs8_bad_password", Test, NULL, setup, test_read_pkcs8_bad_password, teardown);
	g_test_add ("/gkm/data-der/write_pkcs8_plain", Test, NULL, setup, test_write_pkcs8_plain, teardown);
	g_test_add ("/gkm/data-der/write_pkcs8_encrypted", Test, NULL, setup, test_write_pkcs8_encrypted, teardown);

	return g_test_run ();
}
