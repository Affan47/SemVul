static int show_vfsstat(struct seq_file *m, void *v)
{
	struct vfsmount *mnt = v;
	int err = 0;


	if (mnt->mnt_devname) {
		seq_puts(m, "device ");
		mangle(m, mnt->mnt_devname);
	} else
		seq_puts(m, "no device");


	seq_puts(m, " mounted on ");
	seq_path(m, mnt, mnt->mnt_root, " \t\n\\");
	seq_putc(m, ' ');


	seq_puts(m, "with fstype ");
	mangle(m, mnt->mnt_sb->s_type->name);


	if (mnt->mnt_sb->s_op->show_stats) {
		seq_putc(m, ' ');
		err = mnt->mnt_sb->s_op->show_stats(m, mnt);
	}

	seq_putc(m, '\n');
	return err;
}
