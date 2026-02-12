static int sctp_process_hn_param(const struct sctp_association *asoc,
				 union sctp_params param,
				 struct sctp_chunk *chunk,
				 struct sctp_chunk **errp)
{
	__u16 len = ntohs(param.p->length);


	if (*errp)
		sctp_chunk_free(*errp);

	*errp = sctp_make_op_error(asoc, chunk, SCTP_ERROR_DNS_FAILED,
				   param.v, len, 0);


	return 0;
}
