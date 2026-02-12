ns_client_error(ns_client_t *client, isc_result_t result) {
	dns_message_t *message = NULL;
	dns_rcode_t rcode;
	bool trunc = false;

	REQUIRE(NS_CLIENT_VALID(client));

	CTRACE("error");

	message = client->message;

	if (client->rcode_override == -1) {
		rcode = dns_result_torcode(result);
	} else {
		rcode = (dns_rcode_t)(client->rcode_override & 0xfff);
	}

	if (result == ISC_R_MAXSIZE) {
		trunc = true;
	}

#if NS_CLIENT_DROPPORT


	if (rcode == dns_rcode_formerr &&
	    ns_client_dropport(isc_sockaddr_getport(&client->peeraddr)) !=
		    DROPPORT_NO)
	{
		char buf[64];
		isc_buffer_t b;

		isc_buffer_init(&b, buf, sizeof(buf) - 1);
		if (dns_rcode_totext(rcode, &b) != ISC_R_SUCCESS) {
			isc_buffer_putstr(&b, "UNKNOWN RCODE");
		}
		ns_client_log(client, DNS_LOGCATEGORY_SECURITY,
			      NS_LOGMODULE_CLIENT, ISC_LOG_DEBUG(10),
			      "dropped error (%.*s) response: suspicious port",
			      (int)isc_buffer_usedlength(&b), buf);
		ns_client_drop(client, ISC_R_SUCCESS);
		return;
	}
#endif


	if (client->view != NULL && client->view->rrl != NULL) {
		bool wouldlog;
		char log_buf[DNS_RRL_LOG_BUF_LEN];
		dns_rrl_result_t rrl_result;
		int loglevel;

		INSIST(rcode != dns_rcode_noerror &&
		       rcode != dns_rcode_nxdomain);
		if ((client->sctx->options & NS_SERVER_LOGQUERIES) != 0) {
			loglevel = DNS_RRL_LOG_DROP;
		} else {
			loglevel = ISC_LOG_DEBUG(1);
		}
		wouldlog = isc_log_wouldlog(ns_lctx, loglevel);
		rrl_result = dns_rrl(
			client->view, &client->peeraddr, TCP_CLIENT(client),
			dns_rdataclass_in, dns_rdatatype_none, NULL, result,
			client->now, wouldlog, log_buf, sizeof(log_buf));
		if (rrl_result != DNS_RRL_RESULT_OK) {


			if (wouldlog) {
				ns_client_log(client,
					      NS_LOGCATEGORY_QUERY_ERRORS,
					      NS_LOGMODULE_CLIENT, loglevel,
					      "%s", log_buf);
			}


			if (!client->view->rrl->log_only) {
				ns_stats_increment(client->sctx->nsstats,
						   ns_statscounter_ratedropped);
				ns_stats_increment(client->sctx->nsstats,
						   ns_statscounter_dropped);
				ns_client_drop(client, DNS_R_DROP);
				return;
			}
		}
	}


	message->flags &= ~DNS_MESSAGEFLAG_QR;


	message->flags &= ~(DNS_MESSAGEFLAG_AA | DNS_MESSAGEFLAG_AD);
	result = dns_message_reply(message, true);
	if (result != ISC_R_SUCCESS) {


		result = dns_message_reply(message, false);
		if (result != ISC_R_SUCCESS) {
			ns_client_drop(client, result);
			return;
		}
	}

	message->rcode = rcode;
	if (trunc) {
		message->flags |= DNS_MESSAGEFLAG_TC;
	}

	if (rcode == dns_rcode_formerr) {


		if (isc_sockaddr_equal(&client->peeraddr,
				       &client->formerrcache.addr) &&
		    message->id == client->formerrcache.id &&
		    (isc_time_seconds(&client->requesttime) -
		     client->formerrcache.time) < 2)
		{

			ns_client_log(client, NS_LOGCATEGORY_CLIENT,
				      NS_LOGMODULE_CLIENT, ISC_LOG_DEBUG(1),
				      "possible error packet loop, "
				      "FORMERR dropped");
			ns_client_drop(client, result);
			return;
		}
		client->formerrcache.addr = client->peeraddr;
		client->formerrcache.time =
			isc_time_seconds(&client->requesttime);
		client->formerrcache.id = message->id;
	} else if (rcode == dns_rcode_servfail && client->query.qname != NULL &&
		   client->view != NULL && client->view->fail_ttl != 0 &&
		   ((client->attributes & NS_CLIENTATTR_NOSETFC) == 0))
	{


		isc_time_t expire;
		isc_interval_t i;
		uint32_t flags = 0;

		if ((message->flags & DNS_MESSAGEFLAG_CD) != 0) {
			flags = NS_FAILCACHE_CD;
		}

		isc_interval_set(&i, client->view->fail_ttl, 0);
		result = isc_time_nowplusinterval(&expire, &i);
		if (result == ISC_R_SUCCESS) {
			dns_badcache_add(
				client->view->failcache, client->query.qname,
				client->query.qtype, true, flags, &expire);
		}
	}

	ns_client_send(client);
}
