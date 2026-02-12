void sdma_unfreeze(struct hfi1_devdata *dd)
{
	int i;


	for (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i],
				   sdma_event_e82_hw_unfreeze);
}
