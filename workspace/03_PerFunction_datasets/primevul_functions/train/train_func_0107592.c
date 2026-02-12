int bpf_prog_array_copy_to_user(struct bpf_prog_array __rcu *progs,
				__u32 __user *prog_ids, u32 cnt)
{
	struct bpf_prog **prog;
	unsigned long err = 0;
	bool nospc;
	u32 *ids;


	ids = kcalloc(cnt, sizeof(u32), GFP_USER | __GFP_NOWARN);
	if (!ids)
		return -ENOMEM;
	rcu_read_lock();
	prog = rcu_dereference(progs)->progs;
	nospc = bpf_prog_array_copy_core(prog, ids, cnt);
	rcu_read_unlock();
	err = copy_to_user(prog_ids, ids, cnt * sizeof(u32));
	kfree(ids);
	if (err)
		return -EFAULT;
	if (nospc)
		return -ENOSPC;
	return 0;
}
