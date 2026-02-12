static u32 isdn_ppp_mp_get_seq(int short_seq,
			       struct sk_buff *skb, u32 last_seq)
{
	u32 seq;
	int flags = skb->data[0] & (MP_BEGIN_FRAG | MP_END_FRAG);

	if (!short_seq)
	{
		seq = ntohl(*(__be32 *)skb->data) & MP_LONGSEQ_MASK;
		skb_push(skb, 1);
	}
	else
	{


		seq = ntohs(*(__be16 *)skb->data) & MP_SHORTSEQ_MASK;


		if (!(seq &  MP_SHORTSEQ_MAXBIT) &&
		    (last_seq &  MP_SHORTSEQ_MAXBIT) &&
		    (unsigned long)last_seq <= MP_LONGSEQ_MAX)
			seq |= (last_seq + MP_SHORTSEQ_MAX + 1) &
				(~MP_SHORTSEQ_MASK & MP_LONGSEQ_MASK);
		else
			seq |= last_seq & (~MP_SHORTSEQ_MASK & MP_LONGSEQ_MASK);

		skb_push(skb, 3);
	}
	*(u32 *)(skb->data + 1) = seq;

	skb->data[0] = flags;
	return seq;
}
