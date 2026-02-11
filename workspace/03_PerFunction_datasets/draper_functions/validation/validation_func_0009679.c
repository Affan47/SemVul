probe_btrfs(blkid_probe pr, const struct blkid_idmag *mag)
{
	struct btrfs_super_block *bfs;

	bfs = blkid_probe_get_sb(pr, mag, struct btrfs_super_block);
	if (!bfs)
		return -1;

	if (*bfs->label)
		blkid_probe_set_label(pr,
				(unsigned char *) bfs->label,
				sizeof(bfs->label));

	blkid_probe_set_uuid(pr, bfs->fsid);
	blkid_probe_set_uuid_as(pr, bfs->dev_item.uuid, "UUID_SUB");

	return 0;
}
