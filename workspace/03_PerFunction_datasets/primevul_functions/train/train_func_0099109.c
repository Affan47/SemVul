chvt_rndsetup(const void *bp, size_t sz)
{
	register uint32_t h;


	h = lcg_state;
	(void)rndget();
	BAFHFinish_reg(h);

	BAFHUpdateMem_reg(h, &rndsetupstate, sizeof(rndsetupstate));

	BAFHUpdateMem_reg(h, bp, sz);

	BAFHFinish_reg(h);

	return (h);
}
