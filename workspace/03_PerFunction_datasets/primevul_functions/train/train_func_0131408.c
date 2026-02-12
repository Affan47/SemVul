smp_fetch_url_ip(struct proxy *px, struct session *l4, void *l7, unsigned int opt,
                 const struct arg *args, struct sample *smp)
{
	struct http_txn *txn = l7;

	CHECK_HTTP_MESSAGE_FIRST();


	url2sa(txn->req.chn->buf->p + txn->req.sl.rq.u, txn->req.sl.rq.u_l, &l4->req->cons->conn->addr.to);
	if (((struct sockaddr_in *)&l4->req->cons->conn->addr.to)->sin_family != AF_INET)
		return 0;
	smp->type = SMP_T_IPV4;
	smp->data.ipv4 = ((struct sockaddr_in *)&l4->req->cons->conn->addr.to)->sin_addr;


	if (px->options & PR_O_HTTP_PROXY)
		l4->flags |= SN_ADDR_SET;

	smp->flags = 0;
	return 1;
}
