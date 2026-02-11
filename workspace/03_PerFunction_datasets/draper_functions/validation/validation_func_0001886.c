pull(int)
{
    if (!_active)
	return 0;

    bool more;
    Packet *p;
    if (_packet || read_packet(0)) {
	if (_timing
	    && _packet->timestamp_anno() > Timestamp::now() - _time_offset)
	    return 0;
	p = _packet;
	more = read_packet(0);
    } else {
	p = 0;
	more = false;
    }

    if (!more && _end_h)
	_end_h->call_write(ErrorHandler::default_handler());
    return p;
}
