bfa_hwcb_rspq_ack(struct bfa_s *bfa, int rspq, u32 ci)
{
	if (bfa_rspq_ci(bfa, rspq) == ci)
		return;

	bfa_rspq_ci(bfa, rspq) = ci;
	writel(ci, bfa->iocfc.bfa_regs.rme_q_ci[rspq]);
	mmiowb();
}
