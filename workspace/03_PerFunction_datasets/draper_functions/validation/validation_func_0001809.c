bfa_ioim_sgpg_alloc(struct bfa_ioim_s *ioim)
{
	u16	nsgpgs;

	WARN_ON(ioim->nsges <= BFI_SGE_INLINE);


	nsgpgs = BFA_SGPG_NPAGE(ioim->nsges);
	if (!nsgpgs)
		return BFA_TRUE;

	if (bfa_sgpg_malloc(ioim->bfa, &ioim->sgpg_q, nsgpgs)
	    != BFA_STATUS_OK) {
		bfa_sgpg_wait(ioim->bfa, &ioim->iosp->sgpg_wqe, nsgpgs);
		return BFA_FALSE;
	}

	ioim->nsgpgs = nsgpgs;
	ioim->sgpg = bfa_q_first(&ioim->sgpg_q);

	return BFA_TRUE;
}
