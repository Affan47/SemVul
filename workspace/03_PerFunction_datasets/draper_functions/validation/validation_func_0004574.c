test_attribute_consumed (void)
{
	CK_ATTRIBUTE attr;
	gboolean ret;

	attr.type = CKA_LABEL;

	ret = gkm_attribute_consumed (&attr);
	g_assert (ret == FALSE);

	gkm_attribute_consume (&attr);

	ret = gkm_attribute_consumed (&attr);
	g_assert (ret == TRUE);
}
