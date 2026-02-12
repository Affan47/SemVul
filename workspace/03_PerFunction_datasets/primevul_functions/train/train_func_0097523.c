static inline struct resv_map *inode_resv_map(struct inode *inode)
{


	return (struct resv_map *)(&inode->i_data)->private_data;
}
