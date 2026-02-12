static void ucma_cleanup_multicast(struct ucma_context *ctx)
{
	struct ucma_multicast *mc;
	unsigned long index;

	xa_for_each(&multicast_table, index, mc) {
		if (mc->ctx != ctx)
			continue;


		xa_erase(&multicast_table, index);
		kfree(mc);
	}
}
