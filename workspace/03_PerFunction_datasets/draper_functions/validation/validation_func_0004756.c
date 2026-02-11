s5p_mfc_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct s5p_mfc_dev *m_dev = platform_get_drvdata(pdev);
	int ret;

	if (m_dev->num_inst == 0)
		return 0;

	if (test_and_set_bit(0, &m_dev->enter_suspend) != 0) {
		mfc_err("Error: going to suspend for a second time\n");
		return -EIO;
	}


	while (test_and_set_bit(0, &m_dev->hw_lock) != 0) {


		ret = wait_event_interruptible_timeout(m_dev->queue,
			m_dev->int_cond, msecs_to_jiffies(MFC_INT_TIMEOUT));
		if (ret == 0) {
			mfc_err("Waiting for hardware to finish timed out\n");
			clear_bit(0, &m_dev->enter_suspend);
			return -EIO;
		}
	}

	ret = s5p_mfc_sleep(m_dev);
	if (ret) {
		clear_bit(0, &m_dev->enter_suspend);
		clear_bit(0, &m_dev->hw_lock);
	}
	return ret;
}
