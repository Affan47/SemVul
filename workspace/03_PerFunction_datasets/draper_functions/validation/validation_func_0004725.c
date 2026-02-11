rio_interrupt (int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct netdev_private *np = netdev_priv(dev);
	void __iomem *ioaddr = np->ioaddr;
	unsigned int_status;
	int cnt = max_intrloop;
	int handled = 0;

	while (1) {
		int_status = dr16(IntStatus);
		dw16(IntStatus, int_status);
		int_status &= DEFAULT_INTR;
		if (int_status == 0 || --cnt < 0)
			break;
		handled = 1;

		if (int_status & RxDMAComplete)
			receive_packet (dev);

		if ((int_status & (TxDMAComplete|IntRequested))) {
			int tx_status;
			tx_status = dr32(TxStatus);
			if (tx_status & 0x01)
				tx_error (dev, tx_status);

			rio_free_tx (dev, 1);
		}


		if (int_status &
		    (HostError | LinkEvent | UpdateStats))
			rio_error (dev, int_status);
	}
	if (np->cur_tx != np->old_tx)
		dw32(CountDown, 100);
	return IRQ_RETVAL(handled);
}
