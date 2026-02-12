xfs_iunlink_change_backref(
	struct xfs_perag	*pag,
	xfs_agino_t		agino,
	xfs_agino_t		next_unlinked)
{
	struct xfs_iunlink	*iu;
	int			error;


	iu = rhashtable_lookup_fast(&pag->pagi_unlinked_hash, &agino,
			xfs_iunlink_hash_params);
	if (!iu)
		return 0;


	error = rhashtable_remove_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);
	if (error)
		return error;


	if (next_unlinked == NULLAGINO) {
		kmem_free(iu);
		return 0;
	}


	iu->iu_next_unlinked = next_unlinked;
	return xfs_iunlink_insert_backref(pag, iu);
}
