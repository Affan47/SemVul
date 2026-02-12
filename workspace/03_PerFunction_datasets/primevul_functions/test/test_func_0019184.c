static void rpmsg_upref_sleepers(struct virtproc_info *vrp)
{

	mutex_lock(&vrp->tx_lock);


	if (atomic_inc_return(&vrp->sleepers) == 1)

		virtqueue_enable_cb(vrp->svq);

	mutex_unlock(&vrp->tx_lock);
}
