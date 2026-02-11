test_bad_password_then_cancel (Test *test, gconstpointer unused)
{
	CK_RV rv;

	gcr_mock_prompter_expect_password_ok ("bad password", NULL);
	gcr_mock_prompter_expect_password_cancel ();

	rv = (test->module->C_Login) (test->session, CKU_CONTEXT_SPECIFIC, NULL, 0);
	gkm_assert_cmprv (rv, ==, CKR_PIN_INCORRECT);
}
