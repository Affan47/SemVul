create_chunk(struct inode *inode, struct audit_tree *tree)
{
	struct fsnotify_mark *entry;
	struct audit_chunk *chunk = alloc_chunk(1);
	if (!chunk)
		return -ENOMEM;

	entry = &chunk->mark;
	if (fsnotify_add_mark(entry, audit_tree_group, inode, NULL, 0)) {
		fsnotify_put_mark(entry);
		return -ENOSPC;
	}

	spin_lock(&entry->lock);
	spin_lock(&hash_lock);
	if (tree->goner) {
		spin_unlock(&hash_lock);
		chunk->dead = 1;
		spin_unlock(&entry->lock);
		fsnotify_destroy_mark(entry, audit_tree_group);
		fsnotify_put_mark(entry);
		return 0;
	}
	chunk->owners[0].index = (1U << 31);
	chunk->owners[0].owner = tree;
	get_tree(tree);
	list_add(&chunk->owners[0].list, &tree->chunks);
	if (!tree->root) {
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	}
	insert_hash(chunk);
	spin_unlock(&hash_lock);
	spin_unlock(&entry->lock);
	fsnotify_put_mark(entry);
	return 0;
}
