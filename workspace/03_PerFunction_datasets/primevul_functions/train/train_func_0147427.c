static void nfsd4_stop_copy(struct nfsd4_copy *copy)
{

	if (!check_and_set_stop_copy(copy))
		kthread_stop(copy->copy_task);
	nfs4_put_copy(copy);
}
