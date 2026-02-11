hr222_micro_boost(struct pcxhr_mgr *mgr, int level)
{
	unsigned char boost_mask;
	boost_mask = (unsigned char) (level << PCXHR_SELMIC_PREAMPLI_OFFSET);
	if (boost_mask & (~PCXHR_SELMIC_PREAMPLI_MASK))
		return;

	mgr->xlx_selmic &= ~PCXHR_SELMIC_PREAMPLI_MASK;
	mgr->xlx_selmic |= boost_mask;

	PCXHR_OUTPB(mgr, PCXHR_XLX_SELMIC, mgr->xlx_selmic);

	dev_dbg(&mgr->pci->dev, "hr222_micro_boost : set %x\n", boost_mask);
}
