rfc1035_a_ipv4(struct rfc1035_res *res,
	const char *name, struct in_addr **iaptr, unsigned *iasize)
#else
int rfc1035_a(struct rfc1035_res *res,
	const char *name, RFC1035_ADDR **iaptr, unsigned *iasize)
#endif
{
struct	rfc1035_reply *reply;
int	n, o;
char	namebuf[RFC1035_MAXNAMESIZE+1];

	namebuf[0]=0;
	strncat(namebuf, name, RFC1035_MAXNAMESIZE);

	*iasize=0;
	if (rfc1035_resolve_cname(res, namebuf,
		RFC1035_TYPE_A, RFC1035_CLASS_IN, &reply, 0) < 0 ||
		reply == 0 ||
		(n=rfc1035_replysearch_an( res, reply, namebuf, RFC1035_TYPE_A,
			RFC1035_CLASS_IN, 0)) < 0)
	{
		if (reply && reply->rcode != RFC1035_RCODE_NXDOMAIN &&
			reply->rcode != RFC1035_RCODE_NOERROR)
		{
			errno=EAGAIN;
			rfc1035_replyfree(reply);
			return (1);
		}

		if (reply) rfc1035_replyfree(reply);
		errno=ENOENT;
		return (-1);
	}

	for (o=n; o >= 0; o=rfc1035_replysearch_an(res, reply, namebuf,
			RFC1035_TYPE_A, RFC1035_CLASS_IN, o+1))
		++*iasize;

	if ( *iasize == 0 )
	{
		errno=EAGAIN;
		rfc1035_replyfree(reply);
		return (-1);
	}

	if ( (*iaptr=(struct in_addr *)malloc(sizeof(**iaptr)* *iasize)) == 0)
	{
		rfc1035_replyfree(reply);
		return (-1);
	}

	for (*iasize=0; n >= 0; n=rfc1035_replysearch_an(res, reply, namebuf,
			RFC1035_TYPE_A, RFC1035_CLASS_IN, n+1))
	{
		(*iaptr)[*iasize]= reply->allrrs[n]->rr.inaddr;
		++*iasize;
	}

	rfc1035_replyfree(reply);
	return (0);
}
