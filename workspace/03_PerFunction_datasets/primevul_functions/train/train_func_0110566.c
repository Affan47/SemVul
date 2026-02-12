nf_conntrack_hash_sysctl(struct ctl_table *table, int write,
			 void *buffer, size_t *lenp, loff_t *ppos)
{
	int ret;


	nf_conntrack_htable_size_user = nf_conntrack_htable_size;

	ret = proc_dointvec(table, write, buffer, lenp, ppos);
	if (ret < 0 || !write)
		return ret;


	ret = nf_conntrack_hash_resize(nf_conntrack_htable_size_user);


	nf_conntrack_htable_size_user = nf_conntrack_htable_size;
	return ret;
}
