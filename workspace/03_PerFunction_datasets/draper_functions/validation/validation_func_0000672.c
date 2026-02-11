result_item_multi_poldiff_run(result_item_t * item, poldiff_t * diff, int incremental __attribute__ ((unused)))
{
	item->diff = diff;
	memset(item->stats, 0, sizeof(item->stats));
	int i;
	for (i = 0; i < 5; i++) {
		item->data.multi.cached[i] = 0;
		util_text_buffer_clear(item->data.multi.buffers[i]);
	}
}
