struct sctp_chunk *sctp_get_ecne_prepend(struct sctp_association *asoc)
{
	if (!asoc->need_ecne)
		return NULL;


	return sctp_make_ecne(asoc, asoc->last_ecne_tsn);
}
