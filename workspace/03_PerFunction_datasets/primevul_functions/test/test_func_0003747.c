static void virtio_serial_save(QEMUFile *f, void *opaque)
{

    virtio_save(VIRTIO_DEVICE(opaque), f);
}
