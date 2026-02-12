int esp6_input_done2(struct sk_buff *skb, int err)
{
	struct xfrm_state *x = xfrm_input_state(skb);
	struct xfrm_offload *xo = xfrm_offload(skb);
	struct crypto_aead *aead = x->data;
	int hlen = sizeof(struct ip_esp_hdr) + crypto_aead_ivsize(aead);
	int hdr_len = skb_network_header_len(skb);

	if (!xo || !(xo->flags & CRYPTO_DONE))
		kfree(ESP_SKB_CB(skb)->tmp);

	if (unlikely(err))
		goto out;

	err = esp_remove_trailer(skb);
	if (unlikely(err < 0))
		goto out;

	if (x->encap) {
		const struct ipv6hdr *ip6h = ipv6_hdr(skb);
		int offset = skb_network_offset(skb) + sizeof(*ip6h);
		struct xfrm_encap_tmpl *encap = x->encap;
		u8 nexthdr = ip6h->nexthdr;
		__be16 frag_off, source;
		struct udphdr *uh;
		struct tcphdr *th;

		offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);

		if (offset < 0) {
			err = -EINVAL;
			goto out;
		}

		uh = (void *)(skb->data + offset);
		th = (void *)(skb->data + offset);
		hdr_len += offset;

		switch (x->encap->encap_type) {
		case TCP_ENCAP_ESPINTCP:
			source = th->source;
			break;
		case UDP_ENCAP_ESPINUDP:
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			source = uh->source;
			break;
		default:
			WARN_ON_ONCE(1);
			err = -EINVAL;
			goto out;
		}


		if (!ipv6_addr_equal(&ip6h->saddr, &x->props.saddr.in6) ||
		    source != encap->encap_sport) {
			xfrm_address_t ipaddr;

			memcpy(&ipaddr.a6, &ip6h->saddr.s6_addr, sizeof(ipaddr.a6));
			km_new_mapping(x, &ipaddr, source);


		}


		if (x->props.mode == XFRM_MODE_TRANSPORT)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	skb_postpull_rcsum(skb, skb_network_header(skb),
			   skb_network_header_len(skb));
	skb_pull_rcsum(skb, hlen);
	if (x->props.mode == XFRM_MODE_TUNNEL)
		skb_reset_transport_header(skb);
	else
		skb_set_transport_header(skb, -hdr_len);


	if (err == IPPROTO_NONE)
		err = -EINVAL;

out:
	return err;
}
