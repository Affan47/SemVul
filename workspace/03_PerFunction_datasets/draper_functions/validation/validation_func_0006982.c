drbd_debugfs_resource_add(struct drbd_resource *resource)
{
	struct dentry *dentry;
	if (!drbd_debugfs_resources)
		return;

	dentry = debugfs_create_dir(resource->name, drbd_debugfs_resources);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res = dentry;

	dentry = debugfs_create_dir("volumes", resource->debugfs_res);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_volumes = dentry;

	dentry = debugfs_create_dir("connections", resource->debugfs_res);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_connections = dentry;

	dentry = debugfs_create_file("in_flight_summary", S_IRUSR|S_IRGRP,
			resource->debugfs_res, resource,
			&in_flight_summary_fops);
	if (IS_ERR_OR_NULL(dentry))
		goto fail;
	resource->debugfs_res_in_flight_summary = dentry;
	return;

fail:
	drbd_debugfs_resource_cleanup(resource);
	drbd_err(resource, "failed to create debugfs dentry\n");
}
