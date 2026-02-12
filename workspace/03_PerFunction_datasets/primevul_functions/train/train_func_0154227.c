static int __maybe_unused i40e_resume(struct device *dev)
{
	struct i40e_pf *pf = dev_get_drvdata(dev);
	int err;


	if (!test_bit(__I40E_SUSPENDED, pf->state))
		return 0;


	rtnl_lock();


	err = i40e_restore_interrupt_scheme(pf);
	if (err) {
		dev_err(dev, "Cannot restore interrupt scheme: %d\n",
			err);
	}

	clear_bit(__I40E_DOWN, pf->state);
	i40e_reset_and_rebuild(pf, false, true);

	rtnl_unlock();


	clear_bit(__I40E_SUSPENDED, pf->state);


	mod_timer(&pf->service_timer,
		  round_jiffies(jiffies + pf->service_timer_period));

	return 0;
}
