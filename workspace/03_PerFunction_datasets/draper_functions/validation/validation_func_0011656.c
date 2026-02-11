dma_buf_init_debugfs(void)
{
	int err = 0;

	dma_buf_debugfs_dir = debugfs_create_dir("dma_buf", NULL);

	if (IS_ERR(dma_buf_debugfs_dir)) {
		err = PTR_ERR(dma_buf_debugfs_dir);
		dma_buf_debugfs_dir = NULL;
		return err;
	}

	err = dma_buf_debugfs_create_file("bufinfo", dma_buf_describe);

	if (err)
		pr_debug("dma_buf: debugfs: failed to create node bufinfo\n");

	return err;
}
