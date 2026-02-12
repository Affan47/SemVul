static unsigned int selinux_ip_postroute(struct sk_buff *skb,
					 const struct net_device *outdev,
					 u16 family)
{
	u32 secmark_perm;
	u32 peer_sid;
	int ifindex = outdev->ifindex;
	struct sock *sk;
	struct common_audit_data ad;
	struct lsm_network_audit net = {0,};
	char *addrp;
	u8 secmark_active;
	u8 peerlbl_active;


	if (!selinux_policycap_netpeer())
		return selinux_ip_postroute_compat(skb, ifindex, family);

	secmark_active = selinux_secmark_enabled();
	peerlbl_active = selinux_peerlbl_enabled();
	if (!secmark_active && !peerlbl_active)
		return NF_ACCEPT;

	sk = skb_to_full_sk(skb);

#ifdef CONFIG_XFRM


	if (skb_dst(skb) != NULL && skb_dst(skb)->xfrm != NULL &&
	    !(sk && sk_listener(sk)))
		return NF_ACCEPT;
#endif

	if (sk == NULL) {


		if (skb->skb_iif) {
			secmark_perm = PACKET__FORWARD_OUT;
			if (selinux_skb_peerlbl_sid(skb, family, &peer_sid))
				return NF_DROP;
		} else {
			secmark_perm = PACKET__SEND;
			peer_sid = SECINITSID_KERNEL;
		}
	} else if (sk_listener(sk)) {


		u32 skb_sid;
		struct sk_security_struct *sksec;

		sksec = sk->sk_security;
		if (selinux_skb_peerlbl_sid(skb, family, &skb_sid))
			return NF_DROP;


		if (skb_sid == SECSID_NULL) {
			switch (family) {
			case PF_INET:
				if (IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED)
					return NF_ACCEPT;
				break;
			case PF_INET6:
				if (IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED)
					return NF_ACCEPT;
				break;
			default:
				return NF_DROP_ERR(-ECONNREFUSED);
			}
		}
		if (selinux_conn_sid(sksec->sid, skb_sid, &peer_sid))
			return NF_DROP;
		secmark_perm = PACKET__SEND;
	} else {


		struct sk_security_struct *sksec = sk->sk_security;
		peer_sid = sksec->sid;
		secmark_perm = PACKET__SEND;
	}

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netif = ifindex;
	ad.u.net->family = family;
	if (selinux_parse_skb(skb, &ad, &addrp, 0, NULL))
		return NF_DROP;

	if (secmark_active)
		if (avc_has_perm(&selinux_state,
				 peer_sid, skb->secmark,
				 SECCLASS_PACKET, secmark_perm, &ad))
			return NF_DROP_ERR(-ECONNREFUSED);

	if (peerlbl_active) {
		u32 if_sid;
		u32 node_sid;

		if (sel_netif_sid(dev_net(outdev), ifindex, &if_sid))
			return NF_DROP;
		if (avc_has_perm(&selinux_state,
				 peer_sid, if_sid,
				 SECCLASS_NETIF, NETIF__EGRESS, &ad))
			return NF_DROP_ERR(-ECONNREFUSED);

		if (sel_netnode_sid(addrp, family, &node_sid))
			return NF_DROP;
		if (avc_has_perm(&selinux_state,
				 peer_sid, node_sid,
				 SECCLASS_NODE, NODE__SENDTO, &ad))
			return NF_DROP_ERR(-ECONNREFUSED);
	}

	return NF_ACCEPT;
}
