fdevent_select_event_get_revent(fdevents *ev, size_t ndx) {
	int revents = 0;

	if (FD_ISSET(ndx, &(ev->select_read))) {
		revents |= FDEVENT_IN;
	}
	if (FD_ISSET(ndx, &(ev->select_write))) {
		revents |= FDEVENT_OUT;
	}
	if (FD_ISSET(ndx, &(ev->select_error))) {
		revents |= FDEVENT_ERR;
	}

	return revents;
}
