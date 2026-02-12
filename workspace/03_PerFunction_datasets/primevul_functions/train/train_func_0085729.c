tcp_sack_option(struct tcpcb *tp, struct tcphdr *th, u_char *cp, int optlen)
{
	int tmp_olen;
	u_char *tmp_cp;
	struct sackhole *cur, *p, *temp;

	if (!tp->sack_enable)
		return;

	if ((th->th_flags & TH_ACK) == 0)
	       return;

	if (SEQ_LT(th->th_ack, tp->snd_una) ||
	    SEQ_GT(th->th_ack, tp->snd_max))
		return;

	if (optlen <= 2 || (optlen - 2) % TCPOLEN_SACK != 0)
		return;

	tmp_cp = cp + 2;
	tmp_olen = optlen - 2;
	tcpstat_inc(tcps_sack_rcv_opts);
	if (tp->snd_numholes < 0)
		tp->snd_numholes = 0;
	if (tp->t_maxseg == 0)
		panic("tcp_sack_option");
	while (tmp_olen > 0) {
		struct sackblk sack;

		memcpy(&sack.start, tmp_cp, sizeof(tcp_seq));
		sack.start = ntohl(sack.start);
		memcpy(&sack.end, tmp_cp + sizeof(tcp_seq), sizeof(tcp_seq));
		sack.end = ntohl(sack.end);
		tmp_olen -= TCPOLEN_SACK;
		tmp_cp += TCPOLEN_SACK;
		if (SEQ_LEQ(sack.end, sack.start))
			continue;
		if (SEQ_LEQ(sack.end, tp->snd_una))
			continue;
		if (SEQ_GT(th->th_ack, tp->snd_una)) {
			if (SEQ_LT(sack.start, th->th_ack))
				continue;
		}
		if (SEQ_GT(sack.end, tp->snd_max))
			continue;
		if (tp->snd_holes == NULL) {
			tp->snd_holes = (struct sackhole *)
			    pool_get(&sackhl_pool, PR_NOWAIT);
			if (tp->snd_holes == NULL) {

				goto done;
			}
			cur = tp->snd_holes;
			cur->start = th->th_ack;
			cur->end = sack.start;
			cur->rxmit = cur->start;
			cur->next = NULL;
			tp->snd_numholes = 1;
			tp->rcv_lastsack = sack.end;


			cur->dups = min(tcprexmtthresh,
			    ((sack.end - cur->end)/tp->t_maxseg));
			if (cur->dups < 1)
				cur->dups = 1;
			continue;
		}

		p = cur = tp->snd_holes;
		while (cur) {
			if (SEQ_LEQ(sack.end, cur->start))

				break;
			if (SEQ_GEQ(sack.start, cur->end)) {

				cur->dups++;
				if (((sack.end - cur->end)/tp->t_maxseg) >=
				    tcprexmtthresh)
					cur->dups = tcprexmtthresh;
				p = cur;
				cur = cur->next;
				continue;
			}
			if (SEQ_LEQ(sack.start, cur->start)) {

				if (SEQ_GEQ(sack.end, cur->end)) {

					if (p != cur) {
						p->next = cur->next;
						pool_put(&sackhl_pool, cur);
						cur = p->next;
					} else {
						cur = cur->next;
						pool_put(&sackhl_pool, p);
						p = cur;
						tp->snd_holes = p;
					}
					tp->snd_numholes--;
					continue;
				}

				cur->start = sack.end;
				cur->rxmit = SEQ_MAX(cur->rxmit, cur->start);
				p = cur;
				cur = cur->next;
				continue;
			}

			if (SEQ_GEQ(sack.end, cur->end)) {
				cur->end = sack.start;
				cur->rxmit = SEQ_MIN(cur->rxmit, cur->end);
				cur->dups++;
				if (((sack.end - cur->end)/tp->t_maxseg) >=
				    tcprexmtthresh)
					cur->dups = tcprexmtthresh;
				p = cur;
				cur = cur->next;
				continue;
			}
			if (SEQ_LT(cur->start, sack.start) &&
			    SEQ_GT(cur->end, sack.end)) {


				if (tp->snd_numholes >= TCP_SACKHOLE_LIMIT)
					goto done;
				temp = (struct sackhole *)
				    pool_get(&sackhl_pool, PR_NOWAIT);
				if (temp == NULL)
					goto done;
				temp->next = cur->next;
				temp->start = sack.end;
				temp->end = cur->end;
				temp->dups = cur->dups;
				temp->rxmit = SEQ_MAX(cur->rxmit, temp->start);
				cur->end = sack.start;
				cur->rxmit = SEQ_MIN(cur->rxmit, cur->end);
				cur->dups++;
				if (((sack.end - cur->end)/tp->t_maxseg) >=
					tcprexmtthresh)
					cur->dups = tcprexmtthresh;
				cur->next = temp;
				p = temp;
				cur = p->next;
				tp->snd_numholes++;
			}
		}

		if (SEQ_LT(tp->rcv_lastsack, sack.start)) {


			if (tp->snd_numholes >= TCP_SACKHOLE_LIMIT)
				goto done;
			temp = (struct sackhole *)
			    pool_get(&sackhl_pool, PR_NOWAIT);
			if (temp == NULL)
				goto done;
			temp->start = tp->rcv_lastsack;
			temp->end = sack.start;
			temp->dups = min(tcprexmtthresh,
			    ((sack.end - sack.start)/tp->t_maxseg));
			if (temp->dups < 1)
				temp->dups = 1;
			temp->rxmit = temp->start;
			temp->next = 0;
			p->next = temp;
			tp->rcv_lastsack = sack.end;
			tp->snd_numholes++;
		}
	}
done:
	return;
}
