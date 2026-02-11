btrfs_read_sys_chunk_array(void)
{
	struct btrfs_chunk_map_item item;
	struct btrfs_disk_key *key;
	struct btrfs_chunk *chunk;
	int cur;


	cur = 0;
	while (cur < sb.sys_chunk_array_size) {
		key = (struct btrfs_disk_key *)(sb.sys_chunk_array + cur);
		cur += sizeof(*key);
		chunk = (struct btrfs_chunk *)(sb.sys_chunk_array + cur);
		cur += btrfs_chunk_item_size(chunk->num_stripes);

		item.logical = key->offset;
		item.length = chunk->length;
		item.devid = chunk->stripe.devid;
		item.physical = chunk->stripe.offset;
		insert_map(&item);
	}
}
