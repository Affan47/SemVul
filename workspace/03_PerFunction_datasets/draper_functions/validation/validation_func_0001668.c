do_term(struct t3cdev *dev, struct sk_buff *skb)
{
	unsigned int hwtid = get_hwtid(skb);
	unsigned int opcode = get_opcode(skb);
	struct t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	if (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[opcode]) {
		return t3c_tid->client->handlers[opcode] (dev, skb,
							  t3c_tid->ctx);
	} else {
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, opcode);
		return CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	}
}
