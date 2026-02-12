static void rpmsg_downref_sleepers(struct virtproc_info *vrp)
{

	mutex_lock(&vrp->tx_lock);


	if (atomic_dec_and_test(&vrp->sleepers))

		virtqueue_disable_cb(vrp->svq);

	mutex_unlock(&vrp->tx_lock);
}
