static void handle_input(VirtIODevice *vdev, VirtQueue *vq)
{


    VirtIOSerial *vser;
    VirtIOSerialPort *port;
    VirtIOSerialPortClass *vsc;

    vser = VIRTIO_SERIAL(vdev);
    port = find_port_by_vq(vser, vq);

    if (!port) {
        return;
    }
    vsc = VIRTIO_SERIAL_PORT_GET_CLASS(port);


    if (port->guest_connected && port->host_connected && vsc->guest_writable) {
        vsc->guest_writable(port);
    }
}
