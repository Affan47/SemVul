static irqreturn_t fsl_hv_state_change_isr(int irq, void *data)
{
	unsigned int status;
	struct doorbell_isr *dbisr = data;
	int ret;


	fsl_hv_queue_doorbell(dbisr->doorbell);


	ret = fh_partition_get_status(dbisr->partition, &status);
	if (!ret && (status == FH_PARTITION_STOPPED))
		return IRQ_WAKE_THREAD;

	return IRQ_HANDLED;
}
