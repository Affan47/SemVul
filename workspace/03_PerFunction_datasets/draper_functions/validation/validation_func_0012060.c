connect()
{
    state = RUNNING;
    debuglog(("connecting client session to '%s'\n", remote_service));


    unsigned char buf[1600];
    memset(buf, 0, sizeof(buf));
    LAT_SessionData *reply = (LAT_SessionData *)buf;
    int ptr = sizeof(LAT_SessionData);

    buf[ptr++] = 0x01;
    buf[ptr++] = 0x01;
    buf[ptr++] = 0xfe;

    add_string(buf, &ptr, (unsigned char *)remote_service);
    buf[ptr++] = 0x00;

    buf[ptr++] = 0x01;
    buf[ptr++] = 0x02;
    buf[ptr++] = 0x04;
    buf[ptr++] = 0x00;

    buf[ptr++] = 0x05;
    add_string(buf, &ptr, (unsigned char *)ltaname);


    if (remote_port[0] != '\0')
    {
	buf[ptr++] = 0x04;
	add_string(buf, &ptr, (unsigned char *)remote_port);
	buf[ptr++] = 0x00;
    }


    if (request_id)
    {
	debuglog(("Sending request id %d, and port %s\n", request_id, ptyname));
	buf[ptr++] = 2;
	buf[ptr++] = 2;
	buf[ptr++] = request_id & 0xFF;
	buf[ptr++] = request_id >> 8;

	buf[ptr++] = 5;
	add_string(buf, &ptr, (unsigned char *)ptyname);
    }


    reply->header.cmd          = LAT_CCMD_SESSION;
    reply->header.num_slots    = 1;
    reply->slot.remote_session = local_session;
    reply->slot.local_session  = remote_session;
    reply->slot.length         = ptr - sizeof(LAT_SessionData);
    reply->slot.cmd            = 0x9f;

    parent.queue_message(buf, ptr);
}
