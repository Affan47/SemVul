pk_transaction_status_changed_emit (PkTransaction *transaction, PkStatusEnum status)
{
	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);


	if (transaction->priv->status == status)
		return;

	transaction->priv->status = status;


	pk_transaction_emit_property_changed (transaction,
					      "Status",
					      g_variant_new_uint32 (status));
}
