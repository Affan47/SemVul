saa7164_encoder_alloc(
	struct saa7164_port *port,
	struct pci_dev *pci,
	struct video_device *template,
	char *type)
{
	struct video_device *vfd;
	struct saa7164_dev *dev = port->dev;

	dprintk(DBGLVL_ENC, "%s()\n", __func__);

	vfd = video_device_alloc();
	if (NULL == vfd)
		return NULL;

	*vfd = *template;
	snprintf(vfd->name, sizeof(vfd->name), "%s %s (%s)", dev->name,
		type, saa7164_boards[dev->board].name);

	vfd->v4l2_dev  = &dev->v4l2_dev;
	vfd->release = video_device_release;
	return vfd;
}
