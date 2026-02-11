test_add_certificate_pinned_fail (Test *test, gconstpointer unused)
{
	GError *error = NULL;
	gboolean ret;


	test->funcs.C_CreateObject = gck_mock_fail_C_CreateObject;

	ret = gcr_trust_add_pinned_certificate (test->certificate, GCR_PURPOSE_CLIENT_AUTH, "peer", NULL, &error);
	g_assert (ret == FALSE);
	g_assert_error (error, GCK_ERROR, CKR_FUNCTION_FAILED);
	g_clear_error (&error);
}
