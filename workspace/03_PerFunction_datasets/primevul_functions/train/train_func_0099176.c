static int isdn_ppp_skip_ac(struct ippp_struct *is, struct sk_buff *skb)
{
	if (skb->len < 1)
		return -1;

	if (skb->data[0] == 0xff) {
		if (skb->len < 2)
			return -1;

		if (skb->data[1] != 0x03)
			return -1;


		skb_pull(skb, 2);
	} else {
		if (is->pppcfg & SC_REJ_COMP_AC)

			return -1;
	}
	return 0;
}
