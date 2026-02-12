static inline void sctp_ulpq_reap_ordered(struct sctp_ulpq *ulpq)
{
	struct sk_buff *pos, *tmp;
	struct sctp_ulpevent *cevent;
	struct sctp_ulpevent *event;
	struct sctp_stream *in;
	struct sk_buff_head temp;
	__u16 csid, cssn;

	in  = &ulpq->asoc->ssnmap->in;


	skb_queue_head_init(&temp);
	event = NULL;
	sctp_skb_for_each(pos, &ulpq->lobby, tmp) {
		cevent = (struct sctp_ulpevent *) pos->cb;
		csid = cevent->stream;
		cssn = cevent->ssn;

		if (cssn != sctp_ssn_peek(in, csid))
			break;


		sctp_ssn_next(in, csid);

		__skb_unlink(pos, &ulpq->lobby);
		if (!event) {

			event = sctp_skb2event(pos);
			__skb_queue_tail(&temp, sctp_event2skb(event));
		} else {

			__skb_queue_tail(&temp, pos);
		}
	}


	if (event)
		sctp_ulpq_tail_event(ulpq, event);
}
