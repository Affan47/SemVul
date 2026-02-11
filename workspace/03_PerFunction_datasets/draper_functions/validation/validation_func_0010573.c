setup_vq(struct virtio_pci_device *vp_dev,
				  struct virtio_pci_vq_info *info,
				  unsigned index,
				  void (*callback)(struct virtqueue *vq),
				  const char *name,
				  u16 msix_vec)
{
	struct virtqueue *vq;
	unsigned long size;
	u16 num;
	int err;


	iowrite16(index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_SEL);


	num = ioread16(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NUM);
	if (!num || ioread32(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN))
		return ERR_PTR(-ENOENT);

	info->num = num;
	info->msix_vector = msix_vec;

	size = PAGE_ALIGN(vring_size(num, VIRTIO_PCI_VRING_ALIGN));
	info->queue = alloc_pages_exact(size, GFP_KERNEL|__GFP_ZERO);
	if (info->queue == NULL)
		return ERR_PTR(-ENOMEM);


	iowrite32(virt_to_phys(info->queue) >> VIRTIO_PCI_QUEUE_ADDR_SHIFT,
		  vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);


	vq = vring_new_virtqueue(index, info->num,
				 VIRTIO_PCI_VRING_ALIGN, &vp_dev->vdev,
				 true, info->queue, vp_notify, callback, name);
	if (!vq) {
		err = -ENOMEM;
		goto out_activate_queue;
	}

	vq->priv = (void __force *)vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NOTIFY;

	if (msix_vec != VIRTIO_MSI_NO_VECTOR) {
		iowrite16(msix_vec, vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		msix_vec = ioread16(vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		if (msix_vec == VIRTIO_MSI_NO_VECTOR) {
			err = -EBUSY;
			goto out_assign;
		}
	}

	return vq;

out_assign:
	vring_del_virtqueue(vq);
out_activate_queue:
	iowrite32(0, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);
	free_pages_exact(info->queue, size);
	return ERR_PTR(err);
}
