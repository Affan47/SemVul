static int parse_response(unsigned char *buf, int buflen,
			char *question, int qlen,
			uint16_t *type, uint16_t *class, int *ttl,
			unsigned char *response, unsigned int *response_len,
			uint16_t *answers)
{
	struct domain_hdr *hdr = (void *) buf;
	struct domain_question *q;
	unsigned char *ptr;
	uint16_t qdcount = ntohs(hdr->qdcount);
	uint16_t ancount = ntohs(hdr->ancount);
	int err, i;
	uint16_t qtype, qclass;
	unsigned char *next = NULL;
	unsigned int maxlen = *response_len;
	GSList *aliases = NULL, *list;
	char name[NS_MAXDNAME + 1];

	if (buflen < 12)
		return -EINVAL;

	debug("qr %d qdcount %d", hdr->qr, qdcount);


	if (hdr->qr != 1 || qdcount != 1)
		return -EINVAL;

	ptr = buf + sizeof(struct domain_hdr);

	strncpy(question, (char *) ptr, qlen);
	qlen = strlen(question);
	ptr += qlen + 1;

	q = (void *) ptr;
	qtype = ntohs(q->type);


	if (qtype != 1 && qtype != 28)
		return -ENOMSG;

	qclass = ntohs(q->class);

	ptr += 2 + 2;

	err = -ENOMSG;
	*response_len = 0;
	*answers = 0;

	memset(name, 0, sizeof(name));


	for (i = 0; i < ancount; i++) {


		unsigned char rsp[NS_MAXCDNAME];
		unsigned int rsp_len = sizeof(rsp) - 1;
		int ret, rdlen;

		memset(rsp, 0, sizeof(rsp));

		ret = parse_rr(buf, ptr, buf + buflen, rsp, &rsp_len,
			type, class, ttl, &rdlen, &next, name,
			sizeof(name) - 1);
		if (ret != 0) {
			err = ret;
			goto out;
		}


		if (*class != qclass) {
			ptr = next;
			next = NULL;
			continue;
		}


		if (*type == 5 && strncmp(question, name, qlen) == 0) {


			unsigned char *end = NULL;
			int name_len = 0, output_len = 0;

			memset(rsp, 0, sizeof(rsp));
			rsp_len = sizeof(rsp) - 1;


			ret = get_name(0, buf, next - rdlen, buf + buflen,
					rsp, rsp_len, &output_len, &end,
					name, sizeof(name) - 1, &name_len);
			if (ret != 0) {

				ptr = next;
				next = NULL;
				continue;
			}


			aliases = g_slist_prepend(aliases, g_strdup(name));

			ptr = next;
			next = NULL;
			continue;
		}

		if (*type == qtype) {


			if (check_alias(aliases, name) ||
				(!aliases && strncmp(question, name,
							qlen) == 0)) {


				if (*response_len + rsp_len > maxlen) {
					err = -ENOBUFS;
					goto out;
				}
				memcpy(response + *response_len, rsp, rsp_len);
				*response_len += rsp_len;
				(*answers)++;
				err = 0;
			}
		}

		ptr = next;
		next = NULL;
	}

out:
	for (list = aliases; list; list = list->next)
		g_free(list->data);
	g_slist_free(aliases);

	return err;
}
