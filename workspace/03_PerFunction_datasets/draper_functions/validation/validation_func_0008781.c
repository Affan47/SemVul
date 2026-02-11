xfs_stats_clear_proc_handler(
	struct ctl_table	*ctl,
	int			write,
	void			__user *buffer,
	size_t			*lenp,
	loff_t			*ppos)
{
	int		ret, *valp = ctl->data;

	ret = proc_dointvec_minmax(ctl, write, buffer, lenp, ppos);

	if (!ret && write && *valp) {
		xfs_stats_clearall(xfsstats.xs_stats);
		xfs_stats_clear = 0;
	}

	return ret;
}
