free_qname(dns_rrl_t *rrl, dns_rrl_entry_t *e) {
	dns_rrl_qname_buf_t *qbuf;

	qbuf = get_qname(rrl, e);
	if (qbuf != NULL) {
		qbuf->e = NULL;
		ISC_LIST_APPEND(rrl->qname_free, qbuf, link);
	}
}
