test_unsigned_not_set (void)
{
	GNode *asn;
	GBytes *bytes;

	asn = egg_asn1x_create (test_asn1_tab, "TestInteger");
	g_assert (asn);

	bytes = egg_asn1x_get_integer_as_usg (asn);
	g_assert (bytes == NULL);

	egg_asn1x_destroy (asn);
}
