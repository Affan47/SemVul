dgnc_tty_write(struct tty_struct *tty,
			  const unsigned char *buf, int count)
{
	struct channel_t *ch = NULL;
	struct un_t *un = NULL;
	int bufcount = 0, n = 0;
	unsigned long flags;
	ushort head;
	ushort tail;
	ushort tmask;
	uint remain;

	if (!tty || !dgnc_TmpWriteBuf)
		return 0;

	un = tty->driver_data;
	if (!un || un->magic != DGNC_UNIT_MAGIC)
		return 0;

	ch = un->un_ch;
	if (!ch || ch->magic != DGNC_CHANNEL_MAGIC)
		return 0;

	if (!count)
		return 0;


	spin_lock_irqsave(&ch->ch_lock, flags);


	tmask = WQUEUEMASK;
	head = (ch->ch_w_head) & tmask;
	tail = (ch->ch_w_tail) & tmask;

	bufcount = tail - head - 1;
	if (bufcount < 0)
		bufcount += WQUEUESIZE;


	bufcount = dgnc_maxcps_room(tty, bufcount);


	count = min(count, bufcount);


	if (count <= 0)
		goto exit_retry;


	if ((un->un_type == DGNC_PRINT) && !(ch->ch_flags & CH_PRON)) {
		dgnc_wmove(ch, ch->ch_digi.digi_onstr,
			   (int)ch->ch_digi.digi_onlen);
		head = (ch->ch_w_head) & tmask;
		ch->ch_flags |= CH_PRON;
	}


	if ((un->un_type != DGNC_PRINT) && (ch->ch_flags & CH_PRON)) {
		dgnc_wmove(ch, ch->ch_digi.digi_offstr,
			   (int)ch->ch_digi.digi_offlen);
		head = (ch->ch_w_head) & tmask;
		ch->ch_flags &= ~CH_PRON;
	}

	n = count;


	remain = WQUEUESIZE - head;

	if (n >= remain) {
		n -= remain;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head = 0;
		buf += remain;
	}

	if (n > 0) {


		remain = n;
		memcpy(ch->ch_wqueue + head, buf, remain);
		head += remain;
	}

	if (count) {
		head &= tmask;
		ch->ch_w_head = head;
	}


	if ((un->un_type == DGNC_PRINT) && (ch->ch_digi.digi_maxcps > 0)
	    && (ch->ch_digi.digi_bufsize > 0)) {
		ch->ch_cpstime += (HZ * count) / ch->ch_digi.digi_maxcps;
	}

	spin_unlock_irqrestore(&ch->ch_lock, flags);

	if (count) {


		ch->ch_bd->bd_ops->copy_data_from_queue_to_uart(ch);
	}

	return count;

exit_retry:

	spin_unlock_irqrestore(&ch->ch_lock, flags);
	return 0;
}
