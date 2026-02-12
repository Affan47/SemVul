static void *get_a_tx_buf(struct virtproc_info *vrp)
{
	unsigned int len;
	void *ret;


	mutex_lock(&vrp->tx_lock);


	if (vrp->last_sbuf < vrp->num_bufs / 2)
		ret = vrp->sbufs + vrp->buf_size * vrp->last_sbuf++;

	else
		ret = virtqueue_get_buf(vrp->svq, &len);

	mutex_unlock(&vrp->tx_lock);

	return ret;
}
