gru_unlock_kernel_context(int blade_id)
{
	struct gru_blade_state *bs;

	bs = gru_base[blade_id];
	up_read(&bs->bs_kgts_sema);
	STAT(unlock_kernel_context);
}
