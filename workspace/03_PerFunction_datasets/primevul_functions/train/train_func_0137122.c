xfs_iunlink_insert_backref(
	struct xfs_perag	*pag,
	struct xfs_iunlink	*iu)
{
	int			error;

	error = rhashtable_insert_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);


	if (error) {
		WARN(error != -ENOMEM, "iunlink cache insert error %d", error);
		kmem_free(iu);
	}


	if (error != 0 && error != -EEXIST)
		error = 0;
	return error;
}
