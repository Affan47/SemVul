test_get_invalid (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;
	CK_RV rv;

	attr.type = CKA_APPLICATION;
	attr.pValue = NULL;
	attr.ulValueLen = 0;

	rv = gkm_store_get_attribute (test->store, test->object, &attr);
	g_assert (rv == CKR_ATTRIBUTE_TYPE_INVALID);
}
