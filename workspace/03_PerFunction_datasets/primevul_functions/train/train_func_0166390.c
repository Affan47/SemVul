cbq_update(struct cbq_sched_data *q)
{
	struct cbq_class *this = q->tx_class;
	struct cbq_class *cl = this;
	int len = q->tx_len;

	q->tx_class = NULL;

	for ( ; cl; cl = cl->share) {
		long avgidle = cl->avgidle;
		long idle;

		cl->bstats.packets++;
		cl->bstats.bytes += len;


		idle = PSCHED_TDIFF(q->now, cl->last);
		if ((unsigned long)idle > 128*1024*1024) {
			avgidle = cl->maxidle;
		} else {
			idle -= L2T(cl, len);


			avgidle += idle - (avgidle>>cl->ewma_log);
		}

		if (avgidle <= 0) {


			if (avgidle < cl->minidle)
				avgidle = cl->minidle;

			cl->avgidle = avgidle;


			idle = (-avgidle) - ((-avgidle) >> cl->ewma_log);


			idle -= L2T(&q->link, len);
			idle += L2T(cl, len);

			PSCHED_AUDIT_TDIFF(idle);

			PSCHED_TADD2(q->now, idle, cl->undertime);
		} else {


			PSCHED_SET_PASTPERFECT(cl->undertime);
			if (avgidle > cl->maxidle)
				cl->avgidle = cl->maxidle;
			else
				cl->avgidle = avgidle;
		}
		cl->last = q->now;
	}

	cbq_update_toplevel(q, this, q->tx_borrowed);
}
