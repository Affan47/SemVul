chroot_fs_refs(const struct path *old_root, const struct path *new_root)
{
	struct task_struct *g, *p;
	struct fs_struct *fs;
	int count = 0;

	read_lock(&tasklist_lock);
	do_each_thread(g, p) {
		task_lock(p);
		fs = p->fs;
		if (fs) {
			int hits = 0;
			spin_lock(&fs->lock);
			write_seqcount_begin(&fs->seq);
			hits += replace_path(&fs->root, old_root, new_root);
			hits += replace_path(&fs->pwd, old_root, new_root);
			write_seqcount_end(&fs->seq);
			while (hits--) {
				count++;
				path_get(new_root);
			}
			spin_unlock(&fs->lock);
		}
		task_unlock(p);
	} while_each_thread(g, p);
	read_unlock(&tasklist_lock);
	while (count--)
		path_put(old_root);
}
