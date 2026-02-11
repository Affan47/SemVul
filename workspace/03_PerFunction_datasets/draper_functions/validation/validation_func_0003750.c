lanai_setup_tx_vci(struct lanai_dev *lanai, struct lanai_vcc *lvcc,
	const struct atm_qos *qos)
{
	int max_sdu, multiplier;
	if (qos->aal == ATM_AAL0) {
		lvcc->tx.unqueue = vcc_tx_unqueue_aal0;
		max_sdu = ATM_CELL_SIZE - 1;
		multiplier = AAL0_TX_MULTIPLIER;
	} else {
		lvcc->tx.unqueue = vcc_tx_unqueue_aal5;
		max_sdu = qos->txtp.max_sdu;
		multiplier = AAL5_TX_MULTIPLIER;
	}
	return lanai_get_sized_buffer(lanai, &lvcc->tx.buf, max_sdu,
	    multiplier, "TX");
}
