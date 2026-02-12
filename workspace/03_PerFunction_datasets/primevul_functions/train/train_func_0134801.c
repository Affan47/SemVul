static void hugetlbfs_evict_inode(struct inode *inode)
{
	struct resv_map *resv_map;

	remove_inode_hugepages(inode, 0, LLONG_MAX);
	resv_map = (struct resv_map *)inode->i_mapping->private_data;

	if (resv_map)
		resv_map_release(&resv_map->refs);
	clear_inode(inode);
}
