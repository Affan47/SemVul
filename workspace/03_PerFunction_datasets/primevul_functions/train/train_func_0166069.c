static int udp_encap_rcv(struct sock * sk, struct sk_buff *skb)
{
#ifndef CONFIG_XFRM
	return 1;
#else
	struct udp_sock *up = udp_sk(sk);
  	struct udphdr *uh = skb->h.uh;
	struct iphdr *iph;
	int iphlen, len;

	__u8 *udpdata = (__u8 *)uh + sizeof(struct udphdr);
	__be32 *udpdata32 = (__be32 *)udpdata;
	__u16 encap_type = up->encap_type;


	if (udpdata > skb->tail)
		return 1;


	if (!encap_type)
		return 1;

	len = skb->tail - udpdata;

	switch (encap_type) {
	default:
	case UDP_ENCAP_ESPINUDP:

		if (len == 1 && udpdata[0] == 0xff) {
			return 0;
		} else if (len > sizeof(struct ip_esp_hdr) && udpdata32[0] != 0 ) {

			len = sizeof(struct udphdr);
		} else

			return 1;
		break;
	case UDP_ENCAP_ESPINUDP_NON_IKE:

		if (len == 1 && udpdata[0] == 0xff) {
			return 0;
		} else if (len > 2 * sizeof(u32) + sizeof(struct ip_esp_hdr) &&
			   udpdata32[0] == 0 && udpdata32[1] == 0) {


			len = sizeof(struct udphdr) + 2 * sizeof(u32);
		} else

			return 1;
		break;
	}


	if (skb_cloned(skb) && pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
		return 0;


	iph = skb->nh.iph;
	iphlen = iph->ihl << 2;
	iph->tot_len = htons(ntohs(iph->tot_len) - len);
	if (skb->len < iphlen + len) {

		return 0;
	}


	skb->h.raw = skb_pull(skb, len);


	iph->protocol = IPPROTO_ESP;


	return -1;
#endif
}
