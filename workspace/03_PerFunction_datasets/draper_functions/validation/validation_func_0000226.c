test_set_transaction_revert_first (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr, prev;
	gconstpointer value;
	gsize n_value;

	prev.type = CKA_LABEL;
	prev.pValue = "numberone";
	prev.ulValueLen = 9;


	gkm_store_set_attribute (test->store, test->transaction, test->object, &prev);
	gkm_transaction_complete (test->transaction);
	g_assert (gkm_transaction_get_failed (test->transaction) == FALSE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == prev.ulValueLen);
	g_assert (memcmp (prev.pValue, value, n_value) == 0);


	g_object_unref (test->transaction);
	test->transaction = gkm_transaction_new ();

	attr.type = CKA_LABEL;
	attr.pValue = "second";
	attr.ulValueLen = 6;

	gkm_store_set_attribute (test->store, test->transaction, test->object, &attr);
	g_assert (gkm_transaction_get_failed (test->transaction) == FALSE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == attr.ulValueLen);
	g_assert (memcmp (attr.pValue, value, n_value) == 0);

	attr.type = CKA_LABEL;
	attr.pValue = "third";
	attr.ulValueLen = 5;

	gkm_store_set_attribute (test->store, test->transaction, test->object, &attr);
	g_assert (gkm_transaction_get_failed (test->transaction) == FALSE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == attr.ulValueLen);
	g_assert (memcmp (attr.pValue, value, n_value) == 0);


	gkm_transaction_fail (test->transaction, CKR_ATTRIBUTE_VALUE_INVALID);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == attr.ulValueLen);
	g_assert (memcmp (attr.pValue, value, n_value) == 0);


	gkm_transaction_complete (test->transaction);
	g_assert (gkm_transaction_get_failed (test->transaction) == TRUE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == prev.ulValueLen);
	g_assert (memcmp (prev.pValue, value, n_value) == 0);
}
