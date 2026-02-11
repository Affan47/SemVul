xfs_mod_ifree(
	struct xfs_mount	*mp,
	int64_t			delta)
{
	percpu_counter_add(&mp->m_ifree, delta);
	if (percpu_counter_compare(&mp->m_ifree, 0) < 0) {
		ASSERT(0);
		percpu_counter_add(&mp->m_ifree, -delta);
		return -EINVAL;
	}
	return 0;
}
