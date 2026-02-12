static inline void sctp_ulpq_store_reasm(struct sctp_ulpq *ulpq,
					 struct sctp_ulpevent *event)
{
	struct sk_buff *pos;
	struct sctp_ulpevent *cevent;
	__u32 tsn, ctsn;

	tsn = event->tsn;


	pos = skb_peek_tail(&ulpq->reasm);
	if (!pos) {
		__skb_queue_tail(&ulpq->reasm, sctp_event2skb(event));
		return;
	}


	cevent = sctp_skb2event(pos);
	ctsn = cevent->tsn;
	if (TSN_lt(ctsn, tsn)) {
		__skb_queue_tail(&ulpq->reasm, sctp_event2skb(event));
		return;
	}


	skb_queue_walk(&ulpq->reasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		if (TSN_lt(tsn, ctsn))
			break;
	}


	__skb_insert(sctp_event2skb(event), pos->prev, pos, &ulpq->reasm);

}
