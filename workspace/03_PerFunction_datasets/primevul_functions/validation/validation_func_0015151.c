struct sctp_association *sctp_id2assoc(struct sock *sk, sctp_assoc_t id)
{
	struct sctp_association *asoc = NULL;


	if (!sctp_style(sk, UDP)) {


		if (!sctp_sstate(sk, ESTABLISHED) && !sctp_sstate(sk, CLOSING))
			return NULL;


		if (!list_empty(&sctp_sk(sk)->ep->asocs))
			asoc = list_entry(sctp_sk(sk)->ep->asocs.next,
					  struct sctp_association, asocs);
		return asoc;
	}


	if (id <= SCTP_ALL_ASSOC)
		return NULL;

	spin_lock_bh(&sctp_assocs_id_lock);
	asoc = (struct sctp_association *)idr_find(&sctp_assocs_id, (int)id);
	if (asoc && (asoc->base.sk != sk || asoc->base.dead))
		asoc = NULL;
	spin_unlock_bh(&sctp_assocs_id_lock);

	return asoc;
}
