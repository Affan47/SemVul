niu_txc_set_imask(struct niu *np, u64 imask)
{
	unsigned long flags;
	u64 val;

	niu_lock_parent(np, flags);
	val = nr64(TXC_INT_MASK);
	val &= ~TXC_INT_MASK_VAL(np->port);
	val |= (imask << TXC_INT_MASK_VAL_SHIFT(np->port));
	niu_unlock_parent(np, flags);
}
