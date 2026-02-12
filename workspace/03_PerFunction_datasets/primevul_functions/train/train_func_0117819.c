pk_transaction_status_changed_cb (PkBackendJob *job,
				  PkStatusEnum status,
				  PkTransaction *transaction)
{
	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);


	if (status == PK_STATUS_ENUM_WAIT)
		return;


	if (transaction->priv->finished) {
		g_warning ("Already finished, so can't proxy status %s",
			   pk_status_enum_to_string (status));
		return;
	}

	pk_transaction_status_changed_emit (transaction, status);
}
