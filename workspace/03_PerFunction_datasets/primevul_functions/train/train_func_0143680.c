void sdma_freeze_notify(struct hfi1_devdata *dd, int link_down)
{
	int i;
	enum sdma_events event = link_down ? sdma_event_e85_link_down :
					     sdma_event_e80_hw_freeze;


	atomic_set(&dd->sdma_unfreeze_count, dd->num_sdma);


	for (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i], event);


}
