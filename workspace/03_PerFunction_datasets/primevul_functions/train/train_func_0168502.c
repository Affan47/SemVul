void sctp_ulpq_partial_delivery(struct sctp_ulpq *ulpq,
				struct sctp_chunk *chunk,
				gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_association *asoc;

	asoc = ulpq->asoc;


	if (!sctp_sk(asoc->base.sk)->pd_mode) {


		event = sctp_ulpq_retrieve_first(ulpq);

		if (event) {
			sctp_ulpq_tail_event(ulpq, event);
			sctp_sk(asoc->base.sk)->pd_mode = 1;
			ulpq->pd_mode = 1;
			return;
		}
	}
}
