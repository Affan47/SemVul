pk_transaction_allow_cancel_emit (PkTransaction *transaction, gboolean allow_cancel)
{
	g_return_if_fail (PK_IS_TRANSACTION (transaction));


	if (transaction->priv->allow_cancel == allow_cancel)
		return;

	transaction->priv->allow_cancel = allow_cancel;


	g_signal_emit (transaction, signals[SIGNAL_ALLOW_CANCEL_CHANGED], 0, allow_cancel);


	pk_transaction_emit_property_changed (transaction,
					      "AllowCancel",
					      g_variant_new_boolean (allow_cancel));
}
