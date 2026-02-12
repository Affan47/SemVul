pk_transaction_error_code_cb (PkBackendJob *job,
			      PkError *item,
			      PkTransaction *transaction)
{
	PkErrorEnum code;
	g_autofree gchar *details = NULL;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);


	g_object_get (item,
		      "code", &code,
		      "details", &details,
		      NULL);

	if (code == PK_ERROR_ENUM_UNKNOWN) {
		g_warning ("%s emitted 'unknown error'",
			   pk_role_enum_to_string (transaction->priv->role));
	}


	pk_results_set_error_code (transaction->priv->results, item);

	if (!transaction->priv->exclusive && code == PK_ERROR_ENUM_LOCK_REQUIRED) {

		g_debug ("changing transaction to exclusive mode (after failing with lock-required)");
		transaction->priv->exclusive = TRUE;
	} else {

		pk_transaction_error_code_emit (transaction, code, details);
	}
}
