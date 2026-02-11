qib_6120_put_tid(struct qib_devdata *dd, u64 __iomem *tidptr,
			     u32 type, unsigned long pa)
{
	u32 __iomem *tidp32 = (u32 __iomem *)tidptr;
	unsigned long flags;
	int tidx;
	spinlock_t *tidlockp;

	if (!dd->kregbase)
		return;

	if (pa != dd->tidinvalid) {
		if (pa & ((1U << 11) - 1)) {
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			return;
		}
		pa >>= 11;
		if (pa & ~QLOGIC_IB_RT_ADDR_MASK) {
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			return;
		}

		if (type == RCVHQ_RCV_TYPE_EAGER)
			pa |= dd->tidtemplate;
		else
			pa |= 2 << 29;
	}


	tidx = tidptr - dd->egrtidbase;

	tidlockp = (type == RCVHQ_RCV_TYPE_EAGER && tidx < dd->rcvhdrcnt)
		? &dd->cspec->kernel_tid_lock : &dd->cspec->user_tid_lock;
	spin_lock_irqsave(tidlockp, flags);
	qib_write_kreg(dd, kr_scratch, 0xfeeddeaf);
	writel(pa, tidp32);
	qib_write_kreg(dd, kr_scratch, 0xdeadbeef);
	mmiowb();
	spin_unlock_irqrestore(tidlockp, flags);
}
