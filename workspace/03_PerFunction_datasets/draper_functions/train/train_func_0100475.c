mwifiex_11n_delete_tx_ba_stream_tbl_entry(struct mwifiex_private *priv,
				struct mwifiex_tx_ba_stream_tbl *tx_ba_tsr_tbl)
{
	if (!tx_ba_tsr_tbl &&
	    mwifiex_is_tx_ba_stream_ptr_valid(priv, tx_ba_tsr_tbl))
		return;

	mwifiex_dbg(priv->adapter, INFO,
		    "info: tx_ba_tsr_tbl %p\n", tx_ba_tsr_tbl);

	list_del(&tx_ba_tsr_tbl->list);

	kfree(tx_ba_tsr_tbl);
}
