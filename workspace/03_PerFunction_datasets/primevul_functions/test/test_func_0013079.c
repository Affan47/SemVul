static void sctp_control_set_owner_w(struct sctp_chunk *chunk)
{
	struct sctp_association *asoc = chunk->asoc;
	struct sk_buff *skb = chunk->skb;


	if (chunk->auth) {
		chunk->shkey = asoc->shkey;
		sctp_auth_shkey_hold(chunk->shkey);
	}
	skb->sk = asoc ? asoc->base.sk : NULL;
	skb_shinfo(skb)->destructor_arg = chunk;
	skb->destructor = sctp_control_release_owner;
}
