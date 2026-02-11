guess_should_terminate(guess_t *gq, bool verbose)
{
	const char *reason = NULL;

	guess_check(gq);

	if (!guess_query_enabled()) {
		reason = "GUESS disabled";
		goto terminate;
	}

	if (gq->flags & GQ_F_TERMINATED) {
		reason = "terminated";
		goto terminate;
	}

	if (gq->query_acks >= gq->max_ultrapeers) {
		reason = "max amount of successfully queried ultrapeers reached";
		goto terminate;
	}

	if (gq->kept_results >= GUESS_MAX_RESULTS) {
		reason = "max amount of kept results reached";
		goto terminate;
	}

	return FALSE;

terminate:
	if (verbose && GNET_PROPERTY(guess_client_debug) > 1) {
		g_debug("GUESS QUERY[%s] should terminate: %s",
			nid_to_string(&gq->gid), reason);
	}

	return TRUE;
}
