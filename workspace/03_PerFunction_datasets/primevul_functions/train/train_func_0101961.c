void nbt_name_socket_handle_response_packet(struct nbt_name_request *req,
					    struct nbt_name_packet *packet,
					    struct socket_address *src)
{


	if ((packet->operation & NBT_OPCODE) == NBT_OPCODE_WACK) {
		uint32_t ttl;
		if (req->received_wack || packet->ancount < 1) {
			nbt_name_request_destructor(req);
			req->status = NT_STATUS_INVALID_NETWORK_RESPONSE;
			req->state  = NBT_REQUEST_ERROR;
			goto done;
		}
		talloc_free(req->te);


		req->num_retries   = 0;
		req->received_wack = true;


		ttl = packet->answers[0].ttl;
		if ((ttl < (5 + 4*1)) || (ttl > (5 + 4*25))) {
			ttl = 5 + 4*25;
		}
		req->timeout = ttl;
		req->te = tevent_add_timer(req->nbtsock->event_ctx, req,
					   timeval_current_ofs(req->timeout, 0),
					   nbt_name_socket_timeout, req);
		return;
	}


	req->replies = talloc_realloc(req, req->replies, struct nbt_name_reply, req->num_replies+1);
	if (req->replies == NULL) {
		nbt_name_request_destructor(req);
		req->state  = NBT_REQUEST_ERROR;
		req->status = NT_STATUS_NO_MEMORY;
		goto done;
	}

	talloc_steal(req, src);
	req->replies[req->num_replies].dest   = src;
	talloc_steal(req, packet);
	req->replies[req->num_replies].packet = packet;
	req->num_replies++;


	if (req->allow_multiple_replies &&
	    req->num_replies < NBT_MAX_REPLIES) {
		return;
	}

	nbt_name_request_destructor(req);
	req->state  = NBT_REQUEST_DONE;
	req->status = NT_STATUS_OK;

done:
	if (req->async.fn) {
		req->async.fn(req);
	}
}
