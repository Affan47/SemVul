static void sdma_sw_tear_down(struct sdma_engine *sde)
{
	struct sdma_state *ss = &sde->state;


	sdma_put(ss);


	atomic_set(&sde->dd->sdma_unfreeze_count, -1);
	wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
}
