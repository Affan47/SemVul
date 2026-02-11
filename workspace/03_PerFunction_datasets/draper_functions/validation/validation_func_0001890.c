read_file_node_aggr(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct ath_node *an = file->private_data;
	struct ath_softc *sc = an->sc;
	struct ath_atx_tid *tid;
	struct ath_txq *txq;
	u32 len = 0, size = 4096;
	char *buf;
	size_t retval;
	int tidno;

	buf = kzalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (!an->sta->ht_cap.ht_supported) {
		len = scnprintf(buf, size, "%s\n",
				"HT not supported");
		goto exit;
	}

	len = scnprintf(buf, size, "Max-AMPDU: %d\n",
			an->maxampdu);
	len += scnprintf(buf + len, size - len, "MPDU Density: %d\n\n",
			 an->mpdudensity);

	len += scnprintf(buf + len, size - len,
			 "\n%3s%11s%10s%10s%10s%10s%9s%6s%8s\n",
			 "TID", "SEQ_START", "SEQ_NEXT", "BAW_SIZE",
			 "BAW_HEAD", "BAW_TAIL", "BAR_IDX", "SCHED", "PAUSED");

	for (tidno = 0, tid = &an->tid[tidno];
	     tidno < IEEE80211_NUM_TIDS; tidno++, tid++) {
		txq = tid->txq;
		ath_txq_lock(sc, txq);
		if (tid->active) {
			len += scnprintf(buf + len, size - len,
					 "%3d%11d%10d%10d%10d%10d%9d%6d\n",
					 tid->tidno,
					 tid->seq_start,
					 tid->seq_next,
					 tid->baw_size,
					 tid->baw_head,
					 tid->baw_tail,
					 tid->bar_index,
					 !list_empty(&tid->list));
		}
		ath_txq_unlock(sc, txq);
	}
exit:
	retval = simple_read_from_buffer(user_buf, count, ppos, buf, len);
	kfree(buf);

	return retval;
}
