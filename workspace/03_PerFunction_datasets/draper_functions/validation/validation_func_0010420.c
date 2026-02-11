_build_connection_okay_message(stepd_step_rec_t *job)
{
	struct io_buf *msg;
	Buf packbuf;
	struct slurm_io_header header;

	if (_outgoing_buf_free(job)) {
		msg = list_dequeue(job->free_outgoing);
	} else {
		return NULL;
	}

	header.type = SLURM_IO_CONNECTION_TEST;
	header.ltaskid = 0;
	header.gtaskid = 0;
	header.length = 0;

	packbuf = create_buf(msg->data, io_hdr_packed_size());
	if (!packbuf) {
		fatal("Failure to allocate memory for a message header");
		return msg;
	}
	io_hdr_pack(&header, packbuf);
	msg->length = io_hdr_packed_size();
	msg->ref_count = 0;


	packbuf->head = NULL;
	free_buf(packbuf);

	return msg;
}
