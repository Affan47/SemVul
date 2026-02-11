test_write_read_value (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;
	CK_ULONG five = 5;
	gconstpointer value;
	gsize n_value;

	attr.type = CKA_BITS_PER_PIXEL;
	attr.pValue = &five;
	attr.ulValueLen = sizeof (five);

	gkm_store_write_value (test->store, test->transaction, test->object, &attr);

	gkm_transaction_complete (test->transaction);
	g_assert (gkm_transaction_get_result (test->transaction) == CKR_OK);

	value = gkm_store_read_value (test->store, test->object, CKA_BITS_PER_PIXEL, &n_value);
	g_assert (value);
	g_assert (n_value == sizeof (five));
	g_assert (memcmp (value, &five, sizeof (five)) == 0);
}
