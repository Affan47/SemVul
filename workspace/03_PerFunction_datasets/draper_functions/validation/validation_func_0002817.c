pm_init(struct packet_manager *pm, struct device_queue_manager *dqm)
{
	BUG_ON(!dqm);

	pm->dqm = dqm;
	mutex_init(&pm->lock);
	pm->priv_queue = kernel_queue_init(dqm->dev, KFD_QUEUE_TYPE_HIQ);
	if (pm->priv_queue == NULL) {
		mutex_destroy(&pm->lock);
		return -ENOMEM;
	}
	pm->allocated = false;

	return 0;
}
