ceph_vxattrcb_layout(struct ceph_inode_info *ci, char *val,
				   size_t size)
{
	int ret;
	struct ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);
	struct ceph_osd_client *osdc = &fsc->client->osdc;
	s64 pool = ceph_file_layout_pg_pool(ci->i_layout);
	const char *pool_name;
	char buf[128];

	dout("ceph_vxattrcb_layout %p\n", &ci->vfs_inode);
	down_read(&osdc->map_sem);
	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, pool);
	if (pool_name) {
		size_t len = strlen(pool_name);
		ret = snprintf(buf, sizeof(buf),
		"stripe_unit=%lld stripe_count=%lld object_size=%lld pool=",
		(unsigned long long)ceph_file_layout_su(ci->i_layout),
		(unsigned long long)ceph_file_layout_stripe_count(ci->i_layout),
	        (unsigned long long)ceph_file_layout_object_size(ci->i_layout));
		if (!size) {
			ret += len;
		} else if (ret + len > size) {
			ret = -ERANGE;
		} else {
			memcpy(val, buf, ret);
			memcpy(val + ret, pool_name, len);
			ret += len;
		}
	} else {
		ret = snprintf(buf, sizeof(buf),
		"stripe_unit=%lld stripe_count=%lld object_size=%lld pool=%lld",
		(unsigned long long)ceph_file_layout_su(ci->i_layout),
		(unsigned long long)ceph_file_layout_stripe_count(ci->i_layout),
	        (unsigned long long)ceph_file_layout_object_size(ci->i_layout),
		(unsigned long long)pool);
		if (size) {
			if (ret <= size)
				memcpy(val, buf, ret);
			else
				ret = -ERANGE;
		}
	}
	up_read(&osdc->map_sem);
	return ret;
}
