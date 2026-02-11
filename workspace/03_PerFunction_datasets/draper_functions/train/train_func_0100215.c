btree_write_alias(struct super_block *sb, struct logfs_block *block,
		write_alias_t *write_one_alias)
{
	struct object_alias_item *item;
	int err;

	list_for_each_entry(item, &block->item_list, list) {
		err = write_alias_journal(sb, block->ino, block->bix,
				block->level, item->child_no, item->val);
		if (err)
			return err;
	}
	return 0;
}
