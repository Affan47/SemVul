saa7164_cmd_free_seqno(struct saa7164_dev *dev, u8 seqno)
{
	mutex_lock(&dev->lock);
	if ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) {
		dev->cmds[seqno].inuse = 0;
		dev->cmds[seqno].signalled = 0;
		dev->cmds[seqno].timeout = 0;
	}
	mutex_unlock(&dev->lock);
}
