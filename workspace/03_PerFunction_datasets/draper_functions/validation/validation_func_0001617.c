ks_soft_reset(struct ks_net *ks, unsigned op)
{

	ks_wrreg16(ks, KS_IER, 0x0000);
	ks_wrreg16(ks, KS_GRR, op);
	mdelay(10);
	ks_wrreg16(ks, KS_GRR, 0);
	mdelay(1);
}
