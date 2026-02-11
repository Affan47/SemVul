git_pkt_buffer_wants(const git_vector *refs, git_transport_caps *caps, git_buf *buf)
{
	unsigned int i = 0;
	git_remote_head *head;

	if (caps->common) {
		for (; i < refs->length; ++i) {
			head = refs->contents[i];
			if (!head->local)
				break;
		}

		if (buffer_want_with_caps(refs->contents[i], caps, buf) < 0)
			return -1;

		i++;
	}

	for (; i < refs->length; ++i) {
		char oid[GIT_OID_HEXSZ];

		head = refs->contents[i];
		if (head->local)
			continue;

		git_oid_fmt(oid, &head->oid);
		git_buf_put(buf, pkt_want_prefix, strlen(pkt_want_prefix));
		git_buf_put(buf, oid, GIT_OID_HEXSZ);
		git_buf_putc(buf, '\n');
		if (git_buf_oom(buf))
			return -1;
	}

	return git_pkt_buffer_flush(buf);
}
