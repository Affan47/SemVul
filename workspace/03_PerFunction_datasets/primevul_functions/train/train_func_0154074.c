static void i40e_reset_and_rebuild(struct i40e_pf *pf, bool reinit,
				   bool lock_acquired)
{
	int ret;


	ret = i40e_reset(pf);
	if (!ret)
		i40e_rebuild(pf, reinit, lock_acquired);
}
