tcp_update_sack_list(struct tcpcb *tp, tcp_seq rcv_laststart,
    tcp_seq rcv_lastend)
{


	int i, j = 0, count = 0, lastpos = -1;
	struct sackblk sack, firstsack, temp[MAX_SACK_BLKS];


	for (i = 0; i < tp->rcv_numsacks; i++) {
		sack = tp->sackblks[i];
		if (sack.start == 0 && sack.end == 0) {
			count++;
			continue;
		}
		if (SEQ_LEQ(sack.end, tp->rcv_nxt)) {
			tp->sackblks[i].start = tp->sackblks[i].end = 0;
			count++;
		} else {
			temp[j].start = tp->sackblks[i].start;
			temp[j++].end = tp->sackblks[i].end;
		}
	}
	tp->rcv_numsacks -= count;
	if (tp->rcv_numsacks == 0) {
		tcp_clean_sackreport(tp);
		if (SEQ_LT(tp->rcv_nxt, rcv_laststart)) {

			tp->sackblks[0].start = rcv_laststart;
			tp->sackblks[0].end = rcv_lastend;
			tp->rcv_numsacks = 1;
		}
		return;
	}

	for (i = 0; i < tp->rcv_numsacks; i++)
		tp->sackblks[i] = temp[i];
	if (SEQ_GEQ(tp->rcv_nxt, rcv_lastend))
		return;


	firstsack.start = rcv_laststart;
	firstsack.end = rcv_lastend;
	for (i = 0; i < tp->rcv_numsacks; i++) {
		sack = tp->sackblks[i];
		if (SEQ_LT(sack.end, firstsack.start) ||
		    SEQ_GT(sack.start, firstsack.end))
			continue;
		if (sack.start == firstsack.start && sack.end == firstsack.end){


			tp->sackblks[i].start = tp->sackblks[i].end = 0;
			lastpos = i;
			continue;
		}
		if (SEQ_LEQ(sack.start, firstsack.start))
			firstsack.start = sack.start;
		if (SEQ_GEQ(sack.end, firstsack.end))
			firstsack.end = sack.end;
		tp->sackblks[i].start = tp->sackblks[i].end = 0;
		lastpos = i;
	}
	if (lastpos != -1) {
		for (i = 0, j = 1; i < tp->rcv_numsacks; i++) {
			sack = tp->sackblks[i];
			if (sack.start == 0 && sack.end == 0)
				continue;
			temp[j++] = sack;
		}
		tp->rcv_numsacks = j;
		for (i = 1; i < tp->rcv_numsacks; i++)
			tp->sackblks[i] = temp[i];
	} else {
		if (tp->rcv_numsacks < MAX_SACK_BLKS)
			tp->rcv_numsacks++;
		for (i = tp->rcv_numsacks-1; i > 0; i--)
			tp->sackblks[i] = tp->sackblks[i-1];
	}
	tp->sackblks[0] = firstsack;
	return;
}
