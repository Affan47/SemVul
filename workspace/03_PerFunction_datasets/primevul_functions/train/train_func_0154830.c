exit_check(ns_client_t *client) {
	bool destroy_manager = false;
	ns_clientmgr_t *manager = NULL;

	REQUIRE(NS_CLIENT_VALID(client));
	manager = client->manager;

	if (client->state <= client->newstate)
		return (false);

	INSIST(client->newstate < NS_CLIENTSTATE_RECURSING);


	if (client->nupdates == 0 &&
	    client->newstate == NS_CLIENTSTATE_FREED && client->view != NULL)
		dns_view_detach(&client->view);

	if (client->state == NS_CLIENTSTATE_WORKING ||
	    client->state == NS_CLIENTSTATE_RECURSING)
	{
		INSIST(client->newstate <= NS_CLIENTSTATE_READING);


		if (client->nupdates > 0)
			return (true);


		if (client->nsends > 0) {
			isc_socket_t *sock;
			if (TCP_CLIENT(client))
				sock = client->tcpsocket;
			else
				sock = client->udpsocket;
			isc_socket_cancel(sock, client->task,
					  ISC_SOCKCANCEL_SEND);
		}

		if (! (client->nsends == 0 && client->nrecvs == 0 &&
		       client->references == 0))
		{


			return (true);
		}


		if (client->state == NS_CLIENTSTATE_RECURSING) {
			LOCK(&manager->reclock);
			if (ISC_LINK_LINKED(client, rlink))
				ISC_LIST_UNLINK(manager->recursing,
						client, rlink);
			UNLOCK(&manager->reclock);
		}
		ns_client_endrequest(client);

		client->state = NS_CLIENTSTATE_READING;
		INSIST(client->recursionquota == NULL);

		if (NS_CLIENTSTATE_READING == client->newstate) {
			if (!client->pipelined) {
				client_read(client);
				client->newstate = NS_CLIENTSTATE_MAX;
				return (true);
			} else if (client->mortal) {
				client->newstate = NS_CLIENTSTATE_INACTIVE;
			} else
				return (false);
		}
	}

	if (client->state == NS_CLIENTSTATE_READING) {


		INSIST(client->recursionquota == NULL);
		INSIST(client->newstate <= NS_CLIENTSTATE_READY);
		if (client->nreads > 0)
			dns_tcpmsg_cancelread(&client->tcpmsg);
		if (client->nreads != 0) {

			return (true);
		}

		if (client->tcpmsg_valid) {
			dns_tcpmsg_invalidate(&client->tcpmsg);
			client->tcpmsg_valid = false;
		}
		if (client->tcpsocket != NULL) {
			CTRACE("closetcp");
			isc_socket_detach(&client->tcpsocket);
		}

		if (client->tcpquota != NULL)
			isc_quota_detach(&client->tcpquota);

		if (client->timerset) {
			(void)isc_timer_reset(client->timer,
					      isc_timertype_inactive,
					      NULL, NULL, true);
			client->timerset = false;
		}

		client->pipelined = false;

		client->peeraddr_valid = false;

		client->state = NS_CLIENTSTATE_READY;
		INSIST(client->recursionquota == NULL);


		if (client->mortal && TCP_CLIENT(client) && !ns_g_clienttest) {
			LOCK(&client->interface->lock);
			if (client->interface->ntcpcurrent <
				    client->interface->ntcptarget)
				client->mortal = false;
			UNLOCK(&client->interface->lock);
		}


		if (client->mortal) {
			if (client->newstate > NS_CLIENTSTATE_INACTIVE)
				client->newstate = NS_CLIENTSTATE_INACTIVE;
		}

		if (NS_CLIENTSTATE_READY == client->newstate) {
			if (TCP_CLIENT(client)) {
				client_accept(client);
			} else
				client_udprecv(client);
			client->newstate = NS_CLIENTSTATE_MAX;
			return (true);
		}
	}

	if (client->state == NS_CLIENTSTATE_READY) {
		INSIST(client->newstate <= NS_CLIENTSTATE_INACTIVE);


		if (client->naccepts > 0)
			isc_socket_cancel(client->tcplistener, client->task,
					  ISC_SOCKCANCEL_ACCEPT);


		if (! (client->naccepts == 0))
			return (true);


		if (client->nrecvs > 0)
			isc_socket_cancel(client->udpsocket, client->task,
					  ISC_SOCKCANCEL_RECV);


		if (! (client->nrecvs == 0))
			return (true);


		if (client->nctls > 0)
			return (true);


		if (client->interface)
			ns_interface_detach(&client->interface);

		INSIST(client->naccepts == 0);
		INSIST(client->recursionquota == NULL);
		if (client->tcplistener != NULL)
			isc_socket_detach(&client->tcplistener);

		if (client->udpsocket != NULL)
			isc_socket_detach(&client->udpsocket);

		if (client->dispatch != NULL)
			dns_dispatch_detach(&client->dispatch);

		client->attributes = 0;
		client->mortal = false;

		if (client->keytag != NULL) {
			isc_mem_put(client->mctx, client->keytag,
				    client->keytag_len);
			client->keytag_len = 0;
		}


		client->state = NS_CLIENTSTATE_INACTIVE;
		INSIST(client->recursionquota == NULL);

		if (client->state == client->newstate) {
			client->newstate = NS_CLIENTSTATE_MAX;
			if (!ns_g_clienttest && manager != NULL &&
			    !manager->exiting)
				ISC_QUEUE_PUSH(manager->inactive, client,
					       ilink);
			if (client->needshutdown)
				isc_task_shutdown(client->task);
			return (true);
		}
	}

	if (client->state == NS_CLIENTSTATE_INACTIVE) {
		INSIST(client->newstate == NS_CLIENTSTATE_FREED);


		REQUIRE(client->state == NS_CLIENTSTATE_INACTIVE);

		INSIST(client->recursionquota == NULL);
		INSIST(!ISC_QLINK_LINKED(client, ilink));

		if (manager != NULL) {
			LOCK(&manager->listlock);
			ISC_LIST_UNLINK(manager->clients, client, link);
			LOCK(&manager->lock);
			if (manager->exiting &&
			    ISC_LIST_EMPTY(manager->clients))
				destroy_manager = true;
			UNLOCK(&manager->lock);
			UNLOCK(&manager->listlock);
		}

		ns_query_free(client);
		isc_mem_put(client->mctx, client->recvbuf, RECV_BUFFER_SIZE);
		isc_event_free((isc_event_t **)&client->sendevent);
		isc_event_free((isc_event_t **)&client->recvevent);
		isc_timer_detach(&client->timer);
		if (client->delaytimer != NULL)
			isc_timer_detach(&client->delaytimer);

		if (client->tcpbuf != NULL)
			isc_mem_put(client->mctx, client->tcpbuf,
				    TCP_BUFFER_SIZE);
		if (client->opt != NULL) {
			INSIST(dns_rdataset_isassociated(client->opt));
			dns_rdataset_disassociate(client->opt);
			dns_message_puttemprdataset(client->message,
						    &client->opt);
		}
		if (client->keytag != NULL) {
			isc_mem_put(client->mctx, client->keytag,
				    client->keytag_len);
			client->keytag_len = 0;
		}

		dns_message_destroy(&client->message);


		if (client->task != NULL)
			isc_task_detach(&client->task);

		CTRACE("free");
		client->magic = 0;


		if (ns_g_clienttest && isc_mem_references(client->mctx) != 1) {
			isc_mem_stats(client->mctx, stderr);
			INSIST(0);
			ISC_UNREACHABLE();
		}


		DESTROYLOCK(&client->query.fetchlock);

		isc_mem_putanddetach(&client->mctx, client, sizeof(*client));
	}

	if (destroy_manager && manager != NULL)
		clientmgr_destroy(manager);

	return (true);
}
