test_wrap_key (Test *test, gconstpointer unused)
{
	GckMechanism mech = { CKM_MOCK_WRAP, (guchar *)"wrap", 4 };
	GError *error = NULL;
	GAsyncResult *result = NULL;
	GckObject *wrapper, *wrapped;
	gpointer output;
	gsize n_output;

	wrapper = find_key (test->session, CKA_WRAP, 0);
	wrapped = find_key_with_value (test->session, "value");


	output = gck_session_wrap_key (test->session, wrapper, CKM_MOCK_WRAP, wrapped, &n_output, NULL, &error);
	g_assert_no_error (error);
	g_assert (output);
	egg_assert_cmpsize (n_output, ==, 5);
	g_assert (memcmp (output, "value", 5) == 0);
	g_free (output);


	output = gck_session_wrap_key_full (test->session, wrapper, &mech, wrapped, &n_output, NULL, &error);
	g_assert_no_error (error);
	g_assert (output);
	egg_assert_cmpsize (n_output, ==, 5);
	g_assert (memcmp (output, "value", 5) == 0);
	g_free (output);


	mech.type = 0;
	n_output = 0;
	output = gck_session_wrap_key_full (test->session, wrapper, &mech, wrapped, &n_output, NULL, &error);
	g_assert (error != NULL);
	g_assert (!output);
	g_clear_error (&error);
	egg_assert_cmpsize (n_output, ==, 0);


	mech.type = CKM_MOCK_WRAP;
	gck_session_wrap_key_async (test->session, wrapper, &mech, wrapped, NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result != NULL);
	output = gck_session_wrap_key_finish (test->session, result, &n_output, &error);
	g_assert_no_error (error);
	g_assert (output);
	egg_assert_cmpsize (n_output, ==, 5);
	g_assert (memcmp (output, "value", 5) == 0);
	g_object_unref (result);
	g_free (output);


	result = NULL;
	mech.type = 0;
	n_output = 0;
	gck_session_wrap_key_async (test->session, wrapper, &mech, wrapped, NULL, fetch_async_result, &result);
	egg_test_wait_until (500);
	g_assert (result != NULL);
	output = gck_session_wrap_key_finish (test->session, result, &n_output, &error);
	g_assert (error != NULL);
	g_assert (!output);
	g_clear_error (&error);
	egg_assert_cmpsize (n_output, ==, 0);
	g_object_unref (result);

	g_object_unref (wrapper);
	g_object_unref (wrapped);
}
