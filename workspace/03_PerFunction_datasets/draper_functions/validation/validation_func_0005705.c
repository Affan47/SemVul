au_do_flush_dir(struct file *file, fl_owner_t id)
{
	int err;
	aufs_bindex_t bindex, bend;
	struct file *h_file;

	err = 0;
	bend = au_fbend_dir(file);
	for (bindex = au_fbstart(file); !err && bindex <= bend; bindex++) {
		h_file = au_hf_dir(file, bindex);
		if (h_file)
			err = vfsub_flush(h_file, id);
	}
	return err;
}
