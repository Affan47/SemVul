fstReaderDeallocateRvatData(void *ctx)
{
struct fstReaderContext *xc = (struct fstReaderContext *)ctx;
if(xc)
	{
	free(xc->rvat_chain_mem); xc->rvat_chain_mem = NULL;
	free(xc->rvat_frame_data); xc->rvat_frame_data = NULL;
	free(xc->rvat_time_table); xc->rvat_time_table = NULL;
	free(xc->rvat_chain_table); xc->rvat_chain_table = NULL;
	free(xc->rvat_chain_table_lengths); xc->rvat_chain_table_lengths = NULL;

	xc->rvat_data_valid = 0;
	}
}
