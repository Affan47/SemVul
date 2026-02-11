cgroup_writeback_init(void)
{
	isw_wq = alloc_workqueue("inode_switch_wbs", 0, 0);
	if (!isw_wq)
		return -ENOMEM;
	return 0;
}
