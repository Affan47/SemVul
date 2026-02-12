static void cmd_post(char *msgid, int mode)
{
    char *mboxname;
    FILE *f = NULL;
    message_data_t *msg;
    int r = 0;


    if (msgid && my_find_msgid(msgid, &mboxname, NULL)) {

	syslog(LOG_INFO,
	       "dupelim: news article id %s already present in mailbox %s",
	       msgid, mboxname);
	r = NNTP_DONT_SEND;
    }

    if (mode != POST_TAKETHIS) {
	if (r) {
	    prot_printf(nntp_out, "%u %s Do not send article\r\n",
			post_codes[mode].no, msgid ? msgid : "");
	    return;
	}
	else {
	    prot_printf(nntp_out, "%u %s Send article\r\n",
			post_codes[mode].cont, msgid ? msgid : "");
	    if (mode == POST_CHECK) return;
	}
    }


    if (!r) {
	f = tmpfile();
	if (!f) r = IMAP_IOERROR;
    }

    if (f) {
	msg_new(&msg);


	r = savemsg(msg, f);


	if (!r) r = deliver(msg);

	if (!r) {
	    prot_printf(nntp_out, "%u %s Article received ok\r\n",
			post_codes[mode].ok, msg->id ? msg->id : "");
#if 0

	    if (msg->control && !config_mupdate_server) {
		int r1 = 0;


		if (!strncmp(msg->control, "newgroup", 8))
		    r1 = newgroup(msg);
		else if (!strncmp(msg->control, "rmgroup", 7))
		    r1 = rmgroup(msg);
		else if (!strncmp(msg->control, "mvgroup", 7))
		    r1 = mvgroup(msg);
		else if (!strncmp(msg->control, "cancel", 6))
		    r1 = cancel(msg);
		else
		    r1 = NNTP_UNKNOWN_CONTROLMSG;

		if (r1)
		    syslog(LOG_WARNING, "control message '%s' failed: %s",
			   msg->control, error_message(r1));
		else {
		    syslog(LOG_INFO, "control message '%s' succeeded",
			   msg->control);
		}
	    }
#endif
	    if (msg->id) {
		const char *peers = config_getstring(IMAPOPT_NEWSPEER);


		if (peers) {
		    char *tmpbuf, *cur_peer, *next_peer;


		    cur_peer = tmpbuf = xstrdup(peers);

		    while (cur_peer) {

			while (Uisspace(*cur_peer)) cur_peer++;


			if ((next_peer = strchr(cur_peer, ' ')) ||
			    (next_peer = strchr(cur_peer, '\t')))
			    *next_peer++ = '\0';


			feedpeer(cur_peer, msg);


			cur_peer = next_peer;
		    }

		    free(tmpbuf);
		}


		news2mail(msg);
	    }
	}

	msg_free(msg);
	if (stage) append_removestage(stage);
	stage = NULL;
    }
    else {

	spool_copy_msg(nntp_in, NULL);
    }

    if (r) {
	prot_printf(nntp_out, "%u %s Failed receiving article (%s)\r\n",
		    post_codes[mode].fail, msgid ? msgid : "",
		    error_message(r));
    }

    prot_flush(nntp_out);
}
