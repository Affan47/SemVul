client_io_handler_send_test_message(client_io_t *cio, int node_id,
					bool *sent_message)
{
	struct io_buf *msg;
	io_hdr_t header;
	Buf packbuf;
	struct server_io_info *server;
	int rc = SLURM_SUCCESS;
	pthread_mutex_lock(&cio->ioservers_lock);

	server = (struct server_io_info *)cio->ioserver[node_id]->arg;
	if (sent_message)
		*sent_message = false;


	if (cio->ioserver[node_id] == NULL) {
		goto done;
	}


	if (server->out_eof) {
		goto done;
	}


	header.type = SLURM_IO_CONNECTION_TEST;
	header.gtaskid = 0;
	header.ltaskid = 0;
	header.length = 0;

	if (_incoming_buf_free(cio)) {
		msg = list_dequeue(cio->free_incoming);

		msg->length = io_hdr_packed_size();
		msg->ref_count = 1;
		msg->header = header;

		packbuf = create_buf(msg->data, io_hdr_packed_size());
		io_hdr_pack(&header, packbuf);

		packbuf->head = NULL;
		free_buf(packbuf);

		list_enqueue( server->msg_queue, msg );

		if (eio_signal_wakeup(cio->eio) != SLURM_SUCCESS) {
			rc = SLURM_ERROR;
			goto done;
		}
		server->testing_connection = true;
		if (sent_message)
			*sent_message = true;
	} else {
		rc = SLURM_ERROR;
		goto done;
	}
done:
	pthread_mutex_unlock(&cio->ioservers_lock);
	return rc;
}
