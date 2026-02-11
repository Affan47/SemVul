cqm_cleanup(void)
{
	int i;

	if (!cqm_rmid_ptrs)
		return;

	for (i = 0; i < cqm_max_rmid; i++)
		kfree(cqm_rmid_ptrs[i]);

	kfree(cqm_rmid_ptrs);
	cqm_rmid_ptrs = NULL;
	cqm_enabled = false;
}
