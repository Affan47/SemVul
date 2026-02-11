fzstart_proto(qdaemon)
struct sdaemon *qdaemon;
{
	int i;
	achdrval_t tx_hdr,rx_hdr;

	for (i = 0; i < cZstartup_retries; i++) {
		stohdr (0L, tx_hdr);
		tx_hdr[ZF0] = ZPROTOCOL_VERSION;
		if (fZesc_ctl)
			tx_hdr[ZF1] |= TX_ESCCTL;
		switch (izexchange_init (qdaemon, ZINIT, tx_hdr, rx_hdr)) {
		case -1: return FALSE;
		case 0:  continue;
		case 1:  break;
		}
#if 0
		if (rx_hdr[ZF0] == 0) {
			ulog (LOG_ERROR, "Old protocol version, init failed");
			return FALSE;
		}
#endif
		fZesc_ctl = fZesc_ctl || (rx_hdr[ZF1] & TX_ESCCTL) != 0;

		stohdr (0L, tx_hdr);
		switch (izexchange_init (qdaemon, ZDATA, tx_hdr, rx_hdr)) {
		case -1: return FALSE;
		case 0:  continue;
		case 1:  break;
		}

		stohdr (0L, tx_hdr);
		switch (izexchange_init (qdaemon, ZACK, tx_hdr, rx_hdr)) {
		case -1: return FALSE;
		case 0:  continue;
		case 1:  break;
		}

		stohdr (0L, tx_hdr);
		switch (izexchange_init (qdaemon, ZINITEND, tx_hdr, rx_hdr)) {
		case -1: return FALSE;
		case 0:  continue;
		case 1:  break;
		}

		DEBUG_MESSAGE0 (DEBUG_PROTO,
				"fzstart_proto: Protocol started");
		return TRUE;


	}

	ulog (LOG_ERROR, "Protocol init failed");
	return FALSE;
}
