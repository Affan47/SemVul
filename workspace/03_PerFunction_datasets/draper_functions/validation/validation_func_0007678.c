print_net_dev_stats(struct activity *a, int prev, int curr,
				    unsigned long long itv)
{
	int i, j;
	struct stats_net_dev *sndc, *sndp;
	double rxkb, txkb, ifutil;

	if (dis) {
		printf("\n%-11s     IFACE   rxpck/s   txpck/s    rxkB/s    txkB/s"
		       "   rxcmp/s   txcmp/s  rxmcst/s   %%ifutil\n", timestamp[!curr]);
	}

	for (i = 0; i < a->nr; i++) {

		sndc = (struct stats_net_dev *) ((char *) a->buf[curr] + i * a->msize);

		if (!strcmp(sndc->interface, ""))
			continue;

		j = check_net_dev_reg(a, curr, prev, i);
		sndp = (struct stats_net_dev *) ((char *) a->buf[prev] + j * a->msize);

		printf("%-11s %9s", timestamp[curr], sndc->interface);

		rxkb = S_VALUE(sndp->rx_bytes, sndc->rx_bytes, itv);
		txkb = S_VALUE(sndp->tx_bytes, sndc->tx_bytes, itv);

		printf(" %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f",
		       S_VALUE(sndp->rx_packets,    sndc->rx_packets,    itv),
		       S_VALUE(sndp->tx_packets,    sndc->tx_packets,    itv),
		       rxkb / 1024,
		       txkb / 1024,
		       S_VALUE(sndp->rx_compressed, sndc->rx_compressed, itv),
		       S_VALUE(sndp->tx_compressed, sndc->tx_compressed, itv),
		       S_VALUE(sndp->multicast,     sndc->multicast,     itv));

		ifutil = compute_ifutil(sndc, rxkb, txkb);
		printf("    %6.2f\n", ifutil);
	}
}
