static void path_rewrite(struct gps_device_t *session, char *prefix)

{


    char *prefloc;
    for (prefloc = (char *)session->packet.outbuffer;
	 prefloc < (char *)session->packet.outbuffer+session->packet.outbuflen;
	 prefloc++)
	if (strncmp(prefloc, prefix, strlen(prefix)) == 0) {
	    char copy[sizeof(session->packet.outbuffer)];
	    (void)strlcpy(copy,
			  (char *)session->packet.outbuffer,
			  sizeof(copy));
	    prefloc += strlen(prefix);
	    (void)strlcpy(prefloc,
			  session->gpsdata.dev.path,
			  sizeof(session->gpsdata.dev.path));
	    (void)strlcat((char *)session->packet.outbuffer, "#",
			  sizeof(session->packet.outbuffer));
	    (void)strlcat((char *)session->packet.outbuffer,
			  copy + (prefloc-(char *)session->packet.outbuffer),
			  sizeof(session->packet.outbuffer));
	}
    session->packet.outbuflen = strlen((char *)session->packet.outbuffer);
}
