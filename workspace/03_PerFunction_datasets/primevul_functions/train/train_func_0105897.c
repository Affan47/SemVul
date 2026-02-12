int snd_sof_dbg_init(struct snd_sof_dev *sdev)
{
	const struct snd_sof_dsp_ops *ops = sof_ops(sdev);
	const struct snd_sof_debugfs_map *map;
	int i;
	int err;


	sdev->debugfs_root = debugfs_create_dir("sof", NULL);


	INIT_LIST_HEAD(&sdev->dfsentry_list);


	for (i = 0; i < ops->debug_map_count; i++) {
		map = &ops->debug_map[i];

		err = snd_sof_debugfs_io_item(sdev, sdev->bar[map->bar] +
					      map->offset, map->size,
					      map->name, map->access_type);

		if (err < 0)
			return err;
	}

#if IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST)

	err = snd_sof_debugfs_buf_item(sdev, NULL, 0,
				       "ipc_flood_count", 0666);


	if (err < 0)
		return err;


	err = snd_sof_debugfs_buf_item(sdev, NULL, 0,
				       "ipc_flood_duration_ms", 0666);


	if (err < 0)
		return err;
#endif

	return 0;
}
