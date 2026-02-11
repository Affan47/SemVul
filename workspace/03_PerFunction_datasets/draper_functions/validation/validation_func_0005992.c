igb_update_dca(struct igb_q_vector *q_vector)
{
	struct igb_adapter *adapter = q_vector->adapter;
	int cpu = get_cpu();

	if (q_vector->cpu == cpu)
		goto out_no_update;

	if (q_vector->tx.ring)
		igb_update_tx_dca(adapter, q_vector->tx.ring, cpu);

	if (q_vector->rx.ring)
		igb_update_rx_dca(adapter, q_vector->rx.ring, cpu);

	q_vector->cpu = cpu;
out_no_update:
	put_cpu();
}
