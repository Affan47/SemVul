rio_unregister_scan(int mport_id, struct rio_scan *scan_ops)
{
	struct rio_mport *port;
	struct rio_scan_node *scan;

	pr_debug("RIO: %s for mport_id=%d\n", __func__, mport_id);

	if (mport_id != RIO_MPORT_ANY && mport_id >= RIO_MAX_MPORTS)
		return -EINVAL;

	mutex_lock(&rio_mport_list_lock);

	list_for_each_entry(port, &rio_mports, node)
		if (port->id == mport_id ||
		    (mport_id == RIO_MPORT_ANY && port->nscan == scan_ops))
			port->nscan = NULL;

	list_for_each_entry(scan, &rio_scans, node) {
		if (scan->mport_id == mport_id) {
			list_del(&scan->node);
			kfree(scan);
			break;
		}
	}

	mutex_unlock(&rio_mport_list_lock);

	return 0;
}
