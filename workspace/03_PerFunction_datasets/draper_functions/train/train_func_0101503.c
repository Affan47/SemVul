aoechr_error(char *msg)
{
	struct ErrMsg *em;
	char *mp;
	ulong flags, n;

	n = strlen(msg);

	spin_lock_irqsave(&emsgs_lock, flags);

	em = emsgs + emsgs_tail_idx;
	if ((em->flags & EMFL_VALID)) {
bail:		spin_unlock_irqrestore(&emsgs_lock, flags);
		return;
	}

	mp = kmemdup(msg, n, GFP_ATOMIC);
	if (mp == NULL) {
		printk(KERN_ERR "aoe: allocation failure, len=%ld\n", n);
		goto bail;
	}

	em->msg = mp;
	em->flags |= EMFL_VALID;
	em->len = n;

	emsgs_tail_idx++;
	emsgs_tail_idx %= ARRAY_SIZE(emsgs);

	spin_unlock_irqrestore(&emsgs_lock, flags);

	if (nblocked_emsgs_readers)
		complete(&emsgs_comp);
}
