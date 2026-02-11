quota_getquota(struct super_block *sb, int type, qid_t id,
			  void __user *addr)
{
	struct kqid qid;
	struct qc_dqblk fdq;
	struct if_dqblk idq;
	int ret;

	if (!sb->s_qcop->get_dqblk)
		return -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	if (!qid_has_mapping(sb->s_user_ns, qid))
		return -EINVAL;
	ret = sb->s_qcop->get_dqblk(sb, qid, &fdq);
	if (ret)
		return ret;
	copy_to_if_dqblk(&idq, &fdq);
	if (copy_to_user(addr, &idq, sizeof(idq)))
		return -EFAULT;
	return 0;
}
