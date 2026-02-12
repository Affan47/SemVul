parse_sshsig_request(struct sshbuf *msg)
{
	int r;
	struct sshbuf *b;

	if ((b = sshbuf_fromb(msg)) == NULL)
		fatal_f("sshbuf_fromb");

	if ((r = sshbuf_cmp(b, 0, "SSHSIG", 6)) != 0 ||
	    (r = sshbuf_consume(b, 6)) != 0 ||
	    (r = sshbuf_get_cstring(b, NULL, NULL)) != 0 ||
	    (r = sshbuf_get_string_direct(b, NULL, NULL)) != 0 ||
	    (r = sshbuf_get_cstring(b, NULL, NULL)) != 0 ||
	    (r = sshbuf_get_string_direct(b, NULL, NULL)) != 0)
		goto out;
	if (sshbuf_len(b) != 0) {
		r = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	r = 0;
 out:
	sshbuf_free(b);
	return r;
}
