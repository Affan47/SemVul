void sdma_freeze(struct hfi1_devdata *dd)
{
	int i;
	int ret;


	ret = wait_event_interruptible(dd->sdma_unfreeze_wq,
				       atomic_read(&dd->sdma_unfreeze_count) <=
				       0);

	if (ret || atomic_read(&dd->sdma_unfreeze_count) < 0)
		return;


	atomic_set(&dd->sdma_unfreeze_count, dd->num_sdma);


	for (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i], sdma_event_e81_hw_frozen);


	(void)wait_event_interruptible(dd->sdma_unfreeze_wq,
				atomic_read(&dd->sdma_unfreeze_count) <= 0);

}
