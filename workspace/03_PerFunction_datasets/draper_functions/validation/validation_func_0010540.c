fintek_resume(struct pnp_dev *pdev)
{
	struct fintek_dev *fintek = pnp_get_drvdata(pdev);

	fit_dbg("%s called", __func__);


	fintek_enable_cir_irq(fintek);


	fintek_config_mode_enable(fintek);
	fintek_select_logical_dev(fintek, fintek->logical_dev_cir);
	fintek_cr_write(fintek, LOGICAL_DEV_ENABLE, CIR_CR_DEV_EN);

	fintek_config_mode_disable(fintek);

	fintek_cir_regs_init(fintek);

	return 0;
}
