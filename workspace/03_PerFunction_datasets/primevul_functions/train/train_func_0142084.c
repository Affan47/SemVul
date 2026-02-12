evbuffer_search_eol(struct evbuffer *buffer,
    struct evbuffer_ptr *start, size_t *eol_len_out,
    enum evbuffer_eol_style eol_style)
{
	struct evbuffer_ptr it, it2;
	size_t extra_drain = 0;
	int ok = 0;


	if (start && start->internal_.chain == NULL) {
		PTR_NOT_FOUND(&it);
		if (eol_len_out)
			*eol_len_out = extra_drain;
		return it;
	}

	EVBUFFER_LOCK(buffer);

	if (start) {
		memcpy(&it, start, sizeof(it));
	} else {
		it.pos = 0;
		it.internal_.chain = buffer->first;
		it.internal_.pos_in_chain = 0;
	}


	switch (eol_style) {
	case EVBUFFER_EOL_ANY:
		if (evbuffer_find_eol_char(&it) < 0)
			goto done;
		memcpy(&it2, &it, sizeof(it));
		extra_drain = evbuffer_strspn(&it2, "\r\n");
		break;
	case EVBUFFER_EOL_CRLF_STRICT: {
		it = evbuffer_search(buffer, "\r\n", 2, &it);
		if (it.pos < 0)
			goto done;
		extra_drain = 2;
		break;
	}
	case EVBUFFER_EOL_CRLF: {
		ev_ssize_t start_pos = it.pos;

		if (evbuffer_strchr(&it, '\n') < 0)
			goto done;
		extra_drain = 1;

		if (it.pos == start_pos)
			break;


		memcpy(&it2, &it, sizeof(it));
		if (evbuffer_ptr_subtract(buffer, &it2, 1)<0)
			break;
		if (evbuffer_getchr(&it2) == '\r') {
			memcpy(&it, &it2, sizeof(it));
			extra_drain = 2;
		}
		break;
	}
	case EVBUFFER_EOL_LF:
		if (evbuffer_strchr(&it, '\n') < 0)
			goto done;
		extra_drain = 1;
		break;
	case EVBUFFER_EOL_NUL:
		if (evbuffer_strchr(&it, '\0') < 0)
			goto done;
		extra_drain = 1;
		break;
	default:
		goto done;
	}

	ok = 1;
done:
	EVBUFFER_UNLOCK(buffer);

	if (!ok)
		PTR_NOT_FOUND(&it);
	if (eol_len_out)
		*eol_len_out = extra_drain;

	return it;
}
