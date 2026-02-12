static unsigned long ebb_switch_in(bool ebb, struct cpu_hw_events *cpuhw)
{
	unsigned long mmcr0 = cpuhw->mmcr.mmcr0;

	if (!ebb)
		goto out;


	mmcr0 |= MMCR0_EBE | MMCR0_BHRBA | MMCR0_PMCC_U6;


	mmcr0 |= current->thread.mmcr0;


	if (!(current->thread.mmcr0 & MMCR0_PMXE))
		mmcr0 &= ~MMCR0_PMXE;

	mtspr(SPRN_SIAR, current->thread.siar);
	mtspr(SPRN_SIER, current->thread.sier);
	mtspr(SPRN_SDAR, current->thread.sdar);


	mtspr(SPRN_MMCR2, cpuhw->mmcr.mmcr2 | current->thread.mmcr2);

	if (ppmu->flags & PPMU_ARCH_31) {
		mtspr(SPRN_MMCR3, current->thread.mmcr3);
		mtspr(SPRN_SIER2, current->thread.sier2);
		mtspr(SPRN_SIER3, current->thread.sier3);
	}
out:
	return mmcr0;
}
