Logl2Frame(struct IsdnCardState *cs, struct sk_buff *skb, char *buf, int dir)
{
	u_char *ptr;

	ptr = skb->data;

	if (ptr[0] & 1 || !(ptr[1] & 1))
		debugl1(cs, "Address not LAPD");
	else
		debugl1(cs, "%s %s: %s%c (sapi %d, tei %d)",
			(dir ? "<-" : "->"), buf, l2frames(ptr),
			((ptr[0] & 2) >> 1) == dir ? 'C' : 'R', ptr[0] >> 2, ptr[1] >> 1);
}
