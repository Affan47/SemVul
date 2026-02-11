fsl_pwm_calculate_period_cycles(struct fsl_pwm_chip *fpc,
						     unsigned long period_ns,
						     enum fsl_pwm_clk index)
{
	int ret;

	ret = fsl_pwm_calculate_default_ps(fpc, index);
	if (ret) {
		dev_err(fpc->chip.dev,
			"failed to calculate default prescaler: %d\n",
			ret);
		return 0;
	}

	return fsl_pwm_calculate_cycles(fpc, period_ns);
}
