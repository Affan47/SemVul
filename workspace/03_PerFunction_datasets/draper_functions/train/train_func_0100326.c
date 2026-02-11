iguanair_set_tx_mask(struct rc_dev *dev, uint32_t mask)
{
	struct iguanair *ir = dev->priv;

	if (mask > 15)
		return 4;

	mutex_lock(&ir->lock);
	ir->packet->channels = mask << 4;
	mutex_unlock(&ir->lock);

	return 0;
}
