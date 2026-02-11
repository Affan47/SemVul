xenvif_debugfs_addif(struct xenvif *vif)
{
	struct dentry *pfile;
	int i;

	if (IS_ERR_OR_NULL(xen_netback_dbg_root))
		return;

	vif->xenvif_dbg_root = debugfs_create_dir(vif->dev->name,
						  xen_netback_dbg_root);
	if (!IS_ERR_OR_NULL(vif->xenvif_dbg_root)) {
		for (i = 0; i < vif->num_queues; ++i) {
			char filename[sizeof("io_ring_q") + 4];

			snprintf(filename, sizeof(filename), "io_ring_q%d", i);
			pfile = debugfs_create_file(filename,
						    S_IRUSR | S_IWUSR,
						    vif->xenvif_dbg_root,
						    &vif->queues[i],
						    &xenvif_dbg_io_ring_ops_fops);
			if (IS_ERR_OR_NULL(pfile))
				pr_warn("Creation of io_ring file returned %ld!\n",
					PTR_ERR(pfile));
		}
	} else
		netdev_warn(vif->dev,
			    "Creation of vif debugfs dir returned %ld!\n",
			    PTR_ERR(vif->xenvif_dbg_root));
}
