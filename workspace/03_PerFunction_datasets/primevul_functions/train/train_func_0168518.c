void sctp_ulpq_skip(struct sctp_ulpq *ulpq, __u16 sid, __u16 ssn)
{
	struct sctp_stream *in;


	in  = &ulpq->asoc->ssnmap->in;


	if (SSN_lt(ssn, sctp_ssn_peek(in, sid)))
		return;


	sctp_ssn_skip(in, sid, ssn);


	sctp_ulpq_reap_ordered(ulpq);
	return;
}
