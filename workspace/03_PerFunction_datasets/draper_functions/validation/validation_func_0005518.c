dm_sm_disk_create(struct dm_transaction_manager *tm,
				       dm_block_t nr_blocks)
{
	int r;
	struct sm_disk *smd;

	smd = kmalloc(sizeof(*smd), GFP_KERNEL);
	if (!smd)
		return ERR_PTR(-ENOMEM);

	smd->begin = 0;
	smd->nr_allocated_this_transaction = 0;
	memcpy(&smd->sm, &ops, sizeof(smd->sm));

	r = sm_ll_new_disk(&smd->ll, tm);
	if (r)
		goto bad;

	r = sm_ll_extend(&smd->ll, nr_blocks);
	if (r)
		goto bad;

	r = sm_disk_commit(&smd->sm);
	if (r)
		goto bad;

	return &smd->sm;

bad:
	kfree(smd);
	return ERR_PTR(r);
}
