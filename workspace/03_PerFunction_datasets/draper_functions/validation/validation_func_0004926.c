arizona_disable_freerun_sysclk(struct arizona *arizona,
					  struct arizona_sysclk_state *state)
{
	int ret;

	ret = regmap_write(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			   state->sysclk);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to re-apply old SYSCLK settings: %d\n", ret);
		return ret;
	}

	ret = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", ret);
		return ret;
	}

	return 0;
}
