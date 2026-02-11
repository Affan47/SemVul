ssd_routine_start(void *data)
{
	struct ssd_device *dev;

	if (!data) {
		return;
	}
	dev = data;

	dev->routine_tick++;

	if (test_bit(SSD_INIT_WORKQ, &dev->state) && !ssd_busy(dev)) {
		(void)test_and_set_bit(SSD_LOG_HW, &dev->state);
		queue_work(dev->workq, &dev->log_work);
	}

	if ((dev->routine_tick % SSD_HWMON_ROUTINE_TICK) == 0 && test_bit(SSD_INIT_WORKQ, &dev->state)) {
		queue_work(dev->workq, &dev->hwmon_work);
	}

	if ((dev->routine_tick % SSD_CAPMON_ROUTINE_TICK) == 0 && test_bit(SSD_INIT_WORKQ, &dev->state)) {
		queue_work(dev->workq, &dev->capmon_work);
	}

	if ((dev->routine_tick % SSD_CAPMON2_ROUTINE_TICK) == 0 && test_bit(SSD_HWMON_PL_CAP(SSD_PL_CAP), &dev->hwmon) && test_bit(SSD_INIT_WORKQ, &dev->state)) {

		queue_work(dev->workq, &dev->capmon_work);
	}

	if (test_bit(SSD_INIT_WORKQ, &dev->state)) {
		queue_work(dev->workq, &dev->tempmon_work);
	}


	mod_timer(&dev->routine_timer, jiffies + msecs_to_jiffies(SSD_ROUTINE_INTERVAL));
}
