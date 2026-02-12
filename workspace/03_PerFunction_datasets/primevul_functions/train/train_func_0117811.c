pk_transaction_progress_changed_emit (PkTransaction *transaction,
				     guint percentage,
				     guint elapsed,
				     guint remaining)
{
	g_return_if_fail (PK_IS_TRANSACTION (transaction));


	transaction->priv->percentage = percentage;
	transaction->priv->elapsed_time = elapsed;


	pk_transaction_emit_property_changed (transaction,
					      "Percentage",
					      g_variant_new_uint32 (percentage));
	pk_transaction_emit_property_changed (transaction,
					      "ElapsedTime",
					      g_variant_new_uint32 (elapsed));
	pk_transaction_emit_property_changed (transaction,
					      "RemainingTime",
					      g_variant_new_uint32 (remaining));
}
