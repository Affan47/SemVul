static int next_chunk_len(struct mctp_serial *dev)
{
	int i;


	if (dev->txpos == dev->txlen)
		return 0;


	if (needs_escape(dev->txbuf[dev->txpos]))
		return 1;


	for (i = 1; i + dev->txpos + 1 < dev->txlen; i++) {
		if (needs_escape(dev->txbuf[dev->txpos + i + 1]))
			break;
	}

	return i;
}
