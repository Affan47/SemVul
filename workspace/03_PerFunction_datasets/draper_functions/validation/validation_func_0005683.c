dch_fill_fifo(struct IsdnCardState *cs)
{
	int count;
	u_char cmd, *ptr;

	if ((cs->debug & L1_DEB_ISAC) && !(cs->debug & L1_DEB_ISAC_FIFO))
		debugl1(cs, "dch_fill_fifo()");

	if (!cs->tx_skb) return;
	count = cs->tx_skb->len;
	if (count <= 0) return;

	if (count > D_FIFO_SIZE) {
		count = D_FIFO_SIZE;
		cmd   = 0x08;
	} else {
		cmd   = 0x0A;
	}

	ptr = cs->tx_skb->data;
	skb_pull(cs->tx_skb, count);
	cs->tx_cnt += count;
	cs->writeisacfifo(cs, ptr, count);
	cs->writeisac(cs, IPACX_CMDRD, cmd);


	if (test_and_set_bit(FLG_DBUSY_TIMER, &cs->HW_Flags)) {
		debugl1(cs, "dch_fill_fifo dbusytimer running");
		del_timer(&cs->dbusytimer);
	}
	init_timer(&cs->dbusytimer);
	cs->dbusytimer.expires = jiffies + ((DBUSY_TIMER_VALUE * HZ)/1000);
	add_timer(&cs->dbusytimer);

	if (cs->debug & L1_DEB_ISAC_FIFO) {
		char *t = cs->dlog;

		t += sprintf(t, "dch_fill_fifo() cnt %d", count);
		QuickHex(t, ptr, count);
		debugl1(cs, "%s", cs->dlog);
	}
}
