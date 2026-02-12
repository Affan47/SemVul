static inline struct sctp_ulpevent *sctp_ulpq_retrieve_reassembled(struct sctp_ulpq *ulpq)
{
	struct sk_buff *pos;
	struct sctp_ulpevent *cevent;
	struct sk_buff *first_frag = NULL;
	__u32 ctsn, next_tsn;
	struct sctp_ulpevent *retval = NULL;


	next_tsn = 0;


	skb_queue_walk(&ulpq->reasm, pos) {
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		switch (cevent->msg_flags & SCTP_DATA_FRAG_MASK) {
		case SCTP_DATA_FIRST_FRAG:
			first_frag = pos;
			next_tsn = ctsn + 1;
			break;

		case SCTP_DATA_MIDDLE_FRAG:
			if ((first_frag) && (ctsn == next_tsn))
				next_tsn++;
			else
				first_frag = NULL;
			break;

		case SCTP_DATA_LAST_FRAG:
			if (first_frag && (ctsn == next_tsn))
				goto found;
			else
				first_frag = NULL;
			break;
		};

	}
done:
	return retval;
found:
	retval = sctp_make_reassembled_event(&ulpq->reasm, first_frag, pos);
	if (retval)
		retval->msg_flags |= MSG_EOR;
	goto done;
}
