test_unique_file_no_conflict (Test* test, gconstpointer unused)
{
	GkmTransaction *transaction = gkm_transaction_new ();
	const gchar *dirname = "/tmp";
	gchar *result;

	result = gkm_transaction_unique_file (transaction, dirname, "transaction-another");
	g_assert (!gkm_transaction_get_failed (transaction));

	g_assert (result);
	g_assert_cmpstr (result, ==, "transaction-another");

	g_free (result);

	g_object_unref (transaction);
}
