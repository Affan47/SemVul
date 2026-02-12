static inline void *nfc_hdr_put(struct sk_buff *skb, u32 portid, u32 seq,
				int flags, u8 cmd)
{

	return genlmsg_put(skb, portid, seq, &nfc_genl_family, flags, cmd);
}
