ho_addrinfo(struct irs_ho *this, const char *name, const struct addrinfo *pai)
{
	struct pvt *pvt = (struct pvt *)this->private;
	struct hostent *hp;
	struct lcl_res_target q, q2, *p;
	struct addrinfo sentinel, *cur;

	memset(&q, 0, sizeof(q2));
	memset(&q2, 0, sizeof(q2));
	memset(&sentinel, 0, sizeof(sentinel));
	cur = &sentinel;

	switch(pai->ai_family) {
	case AF_UNSPEC:
		q.family = AF_INET6;
		q.next = &q2;
		q2.family = AF_INET;
		break;
	case AF_INET6:
		q.family = AF_INET6;
		break;
	case AF_INET:
		q.family = AF_INET;
		break;
	default:
		RES_SET_H_ERRNO(pvt->res, NO_RECOVERY);
		return(NULL);
	}

	for (p = &q; p; p = p->next) {
		struct addrinfo *ai;

		hp = (*this->byname2)(this, name, p->family);
		if (hp == NULL) {

			continue;
		}
		if ((hp->h_name == NULL) || (hp->h_name[0] == 0) ||
		    (hp->h_addr_list[0] == NULL)) {
			RES_SET_H_ERRNO(pvt->res, NO_RECOVERY);
			continue;
		}

		ai = hostent2addrinfo(hp, pai);
		if (ai) {
			cur->ai_next = ai;
			while (cur->ai_next)
				cur = cur->ai_next;
		}
	}

	if (sentinel.ai_next == NULL)
		RES_SET_H_ERRNO(pvt->res, HOST_NOT_FOUND);

	return(sentinel.ai_next);
}
