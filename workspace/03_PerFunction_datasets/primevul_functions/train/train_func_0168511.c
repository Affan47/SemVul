static struct sctp_ulpevent *sctp_ulpq_order(struct sctp_ulpq *ulpq,
					     struct sctp_ulpevent *event)
{
	__u16 sid, ssn;
	struct sctp_stream *in;


	if (SCTP_DATA_UNORDERED & event->msg_flags)
		return event;


	sid = event->stream;
	ssn = event->ssn;
	in  = &ulpq->asoc->ssnmap->in;


	if (ssn != sctp_ssn_peek(in, sid)) {


		sctp_ulpq_store_ordered(ulpq, event);
		return NULL;
	}


	sctp_ssn_next(in, sid);


	sctp_ulpq_retrieve_ordered(ulpq, event);

	return event;
}
