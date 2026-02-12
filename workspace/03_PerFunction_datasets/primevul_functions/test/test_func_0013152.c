void sctp_chunk_assign_ssn(struct sctp_chunk *chunk)
{
	struct sctp_stream *stream;
	struct sctp_chunk *lchunk;
	struct sctp_datamsg *msg;
	__u16 ssn, sid;

	if (chunk->has_ssn)
		return;


	sid = ntohs(chunk->subh.data_hdr->stream);
	stream = &chunk->asoc->stream;


	msg = chunk->msg;
	list_for_each_entry(lchunk, &msg->chunks, frag_list) {
		if (lchunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) {
			ssn = 0;
		} else {
			if (lchunk->chunk_hdr->flags & SCTP_DATA_LAST_FRAG)
				ssn = sctp_ssn_next(stream, out, sid);
			else
				ssn = sctp_ssn_peek(stream, out, sid);
		}

		lchunk->subh.data_hdr->ssn = htons(ssn);
		lchunk->has_ssn = 1;
	}
}
