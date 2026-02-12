static void ccp_update_sg_workarea(struct ccp_sg_workarea *wa, unsigned int len)
{
	unsigned int nbytes = min_t(u64, len, wa->bytes_left);
	unsigned int sg_combined_len = 0;

	if (!wa->sg)
		return;

	wa->sg_used += nbytes;
	wa->bytes_left -= nbytes;
	if (wa->sg_used == sg_dma_len(wa->dma_sg)) {

		wa->dma_sg = sg_next(wa->dma_sg);


		do {
			sg_combined_len += wa->sg->length;
			wa->sg = sg_next(wa->sg);
		} while (wa->sg_used > sg_combined_len);

		wa->sg_used = 0;
	}
}
