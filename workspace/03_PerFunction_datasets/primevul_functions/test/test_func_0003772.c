int virtio_serial_open(VirtIOSerialPort *port)
{

    if (port->host_connected) {
        return 0;
    }

    port->host_connected = true;
    send_control_event(port->vser, port->id, VIRTIO_CONSOLE_PORT_OPEN, 1);

    return 0;
}
