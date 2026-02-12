static int sctp_get_port_local(struct sock *sk, union sctp_addr *addr)
{
	struct sctp_sock *sp = sctp_sk(sk);
	bool reuse = (sk->sk_reuse || sp->reuse);
	struct sctp_bind_hashbucket *head;
	struct net *net = sock_net(sk);
	kuid_t uid = sock_i_uid(sk);
	struct sctp_bind_bucket *pp;
	unsigned short snum;
	int ret;

	snum = ntohs(addr->v4.sin_port);

	pr_debug("%s: begins, snum:%d\n", __func__, snum);

	if (snum == 0) {

		int low, high, remaining, index;
		unsigned int rover;

		inet_get_local_port_range(net, &low, &high);
		remaining = (high - low) + 1;
		rover = prandom_u32() % remaining + low;

		do {
			rover++;
			if ((rover < low) || (rover > high))
				rover = low;
			if (inet_is_local_reserved_port(net, rover))
				continue;
			index = sctp_phashfn(net, rover);
			head = &sctp_port_hashtable[index];
			spin_lock_bh(&head->lock);
			sctp_for_each_hentry(pp, &head->chain)
				if ((pp->port == rover) &&
				    net_eq(net, pp->net))
					goto next;
			break;
		next:
			spin_unlock_bh(&head->lock);
			cond_resched();
		} while (--remaining > 0);


		ret = 1;
		if (remaining <= 0)
			return ret;


		snum = rover;
	} else {


		head = &sctp_port_hashtable[sctp_phashfn(net, snum)];
		spin_lock_bh(&head->lock);
		sctp_for_each_hentry(pp, &head->chain) {
			if ((pp->port == snum) && net_eq(pp->net, net))
				goto pp_found;
		}
	}
	pp = NULL;
	goto pp_not_found;
pp_found:
	if (!hlist_empty(&pp->owner)) {


		struct sock *sk2;

		pr_debug("%s: found a possible match\n", __func__);

		if ((pp->fastreuse && reuse &&
		     sk->sk_state != SCTP_SS_LISTENING) ||
		    (pp->fastreuseport && sk->sk_reuseport &&
		     uid_eq(pp->fastuid, uid)))
			goto success;


		sk_for_each_bound(sk2, &pp->owner) {
			struct sctp_sock *sp2 = sctp_sk(sk2);
			struct sctp_endpoint *ep2 = sp2->ep;

			if (sk == sk2 ||
			    (reuse && (sk2->sk_reuse || sp2->reuse) &&
			     sk2->sk_state != SCTP_SS_LISTENING) ||
			    (sk->sk_reuseport && sk2->sk_reuseport &&
			     uid_eq(uid, sock_i_uid(sk2))))
				continue;

			if (sctp_bind_addr_conflict(&ep2->base.bind_addr,
						    addr, sp2, sp)) {
				ret = 1;
				goto fail_unlock;
			}
		}

		pr_debug("%s: found a match\n", __func__);
	}
pp_not_found:

	ret = 1;
	if (!pp && !(pp = sctp_bucket_create(head, net, snum)))
		goto fail_unlock;


	if (hlist_empty(&pp->owner)) {
		if (reuse && sk->sk_state != SCTP_SS_LISTENING)
			pp->fastreuse = 1;
		else
			pp->fastreuse = 0;

		if (sk->sk_reuseport) {
			pp->fastreuseport = 1;
			pp->fastuid = uid;
		} else {
			pp->fastreuseport = 0;
		}
	} else {
		if (pp->fastreuse &&
		    (!reuse || sk->sk_state == SCTP_SS_LISTENING))
			pp->fastreuse = 0;

		if (pp->fastreuseport &&
		    (!sk->sk_reuseport || !uid_eq(pp->fastuid, uid)))
			pp->fastreuseport = 0;
	}


success:
	if (!sp->bind_hash) {
		inet_sk(sk)->inet_num = snum;
		sk_add_bind_node(sk, &pp->owner);
		sp->bind_hash = pp;
	}
	ret = 0;

fail_unlock:
	spin_unlock_bh(&head->lock);
	return ret;
}
