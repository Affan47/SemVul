static void pmao_restore_workaround(bool ebb)
{
	unsigned pmcs[6];

	if (!cpu_has_feature(CPU_FTR_PMAO_BUG))
		return;


	if ((current->thread.mmcr0 & (MMCR0_PMAO | MMCR0_PMAO_SYNC)) != MMCR0_PMAO)
		return;


	if (ebb && !(current->thread.bescr & BESCR_GE))
		return;


	hard_irq_disable();


	pmcs[0] = mfspr(SPRN_PMC1);
	pmcs[1] = mfspr(SPRN_PMC2);
	pmcs[2] = mfspr(SPRN_PMC3);
	pmcs[3] = mfspr(SPRN_PMC4);
	pmcs[4] = mfspr(SPRN_PMC5);
	pmcs[5] = mfspr(SPRN_PMC6);


	mtspr(SPRN_MMCR2, 0);


	mtspr(SPRN_PMC6, 0x7FFFFFFE);


	mtspr(SPRN_MMCR0, MMCR0_PMXE | MMCR0_PMCjCE | MMCR0_PMAO);


	mtspr(SPRN_MMCR0, MMCR0_FC | MMCR0_PMAO);

	mtspr(SPRN_PMC1, pmcs[0]);
	mtspr(SPRN_PMC2, pmcs[1]);
	mtspr(SPRN_PMC3, pmcs[2]);
	mtspr(SPRN_PMC4, pmcs[3]);
	mtspr(SPRN_PMC5, pmcs[4]);
	mtspr(SPRN_PMC6, pmcs[5]);
}
