fimc_is_suspend(struct device *dev)
{
	struct fimc_is *is = dev_get_drvdata(dev);


	if (test_bit(IS_ST_A5_PWR_ON, &is->state))
		return -EBUSY;

	return 0;
}
