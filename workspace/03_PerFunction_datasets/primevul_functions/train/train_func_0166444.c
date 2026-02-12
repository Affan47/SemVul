static int tc_modify_qdisc(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct tcmsg *tcm;
	struct rtattr **tca;
	struct net_device *dev;
	u32 clid;
	struct Qdisc *q, *p;
	int err;

replay:

	tcm = NLMSG_DATA(n);
	tca = arg;
	clid = tcm->tcm_parent;
	q = p = NULL;

	if ((dev = __dev_get_by_index(tcm->tcm_ifindex)) == NULL)
		return -ENODEV;

	if (clid) {
		if (clid != TC_H_ROOT) {
			if (clid != TC_H_INGRESS) {
				if ((p = qdisc_lookup(dev, TC_H_MAJ(clid))) == NULL)
					return -ENOENT;
				q = qdisc_leaf(p, clid);
			} else {
				q = dev->qdisc_ingress;
			}
		} else {
			q = dev->qdisc_sleeping;
		}


		if (q && q->handle == 0)
			q = NULL;

		if (!q || !tcm->tcm_handle || q->handle != tcm->tcm_handle) {
			if (tcm->tcm_handle) {
				if (q && !(n->nlmsg_flags&NLM_F_REPLACE))
					return -EEXIST;
				if (TC_H_MIN(tcm->tcm_handle))
					return -EINVAL;
				if ((q = qdisc_lookup(dev, tcm->tcm_handle)) == NULL)
					goto create_n_graft;
				if (n->nlmsg_flags&NLM_F_EXCL)
					return -EEXIST;
				if (tca[TCA_KIND-1] && rtattr_strcmp(tca[TCA_KIND-1], q->ops->id))
					return -EINVAL;
				if (q == p ||
				    (p && check_loop(q, p, 0)))
					return -ELOOP;
				atomic_inc(&q->refcnt);
				goto graft;
			} else {
				if (q == NULL)
					goto create_n_graft;


				if ((n->nlmsg_flags&NLM_F_CREATE) &&
				    (n->nlmsg_flags&NLM_F_REPLACE) &&
				    ((n->nlmsg_flags&NLM_F_EXCL) ||
				     (tca[TCA_KIND-1] &&
				      rtattr_strcmp(tca[TCA_KIND-1], q->ops->id))))
					goto create_n_graft;
			}
		}
	} else {
		if (!tcm->tcm_handle)
			return -EINVAL;
		q = qdisc_lookup(dev, tcm->tcm_handle);
	}


	if (q == NULL)
		return -ENOENT;
	if (n->nlmsg_flags&NLM_F_EXCL)
		return -EEXIST;
	if (tca[TCA_KIND-1] && rtattr_strcmp(tca[TCA_KIND-1], q->ops->id))
		return -EINVAL;
	err = qdisc_change(q, tca);
	if (err == 0)
		qdisc_notify(skb, n, clid, NULL, q);
	return err;

create_n_graft:
	if (!(n->nlmsg_flags&NLM_F_CREATE))
		return -ENOENT;
	if (clid == TC_H_INGRESS)
		q = qdisc_create(dev, tcm->tcm_parent, tca, &err);
        else
		q = qdisc_create(dev, tcm->tcm_handle, tca, &err);
	if (q == NULL) {
		if (err == -EAGAIN)
			goto replay;
		return err;
	}

graft:
	if (1) {
		struct Qdisc *old_q = NULL;
		err = qdisc_graft(dev, p, clid, q, &old_q);
		if (err) {
			if (q) {
				spin_lock_bh(&dev->queue_lock);
				qdisc_destroy(q);
				spin_unlock_bh(&dev->queue_lock);
			}
			return err;
		}
		qdisc_notify(skb, n, clid, old_q, q);
		if (old_q) {
			spin_lock_bh(&dev->queue_lock);
			qdisc_destroy(old_q);
			spin_unlock_bh(&dev->queue_lock);
		}
	}
	return 0;
}
