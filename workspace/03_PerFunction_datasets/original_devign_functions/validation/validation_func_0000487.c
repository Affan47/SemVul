static ssize_t flush_buf(VirtIOSerialPort *port, const uint8_t *buf, ssize_t len) {
    VirtConsole *vcon = VIRTIO_CONSOLE(port);
    ssize_t ret;
    if (!vcon->chr) {
        return len;
    }
    ret = qemu_chr_fe_write(vcon->chr, buf, len);
    trace_virtio_console_flush_buf(port->id, len, ret);
    if (ret < len) {
        VirtIOSerialPortClass *k = VIRTIO_SERIAL_PORT_GET_CLASS(port);
