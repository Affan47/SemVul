static void handle_control_message(VirtIOSerial *vser, void *buf, size_t len)
{
    VirtIODevice *vdev = VIRTIO_DEVICE(vser);
    struct VirtIOSerialPort *port;
    VirtIOSerialPortClass *vsc;
    struct virtio_console_control cpkt, *gcpkt;
    uint8_t *buffer;
    size_t buffer_len;

    gcpkt = buf;

    if (len < sizeof(cpkt)) {

        return;
    }

    cpkt.event = virtio_lduw_p(vdev, &gcpkt->event);
    cpkt.value = virtio_lduw_p(vdev, &gcpkt->value);

    trace_virtio_serial_handle_control_message(cpkt.event, cpkt.value);

    if (cpkt.event == VIRTIO_CONSOLE_DEVICE_READY) {
        if (!cpkt.value) {
            error_report("virtio-serial-bus: Guest failure in adding device %s",
                         vser->bus.qbus.name);
            return;
        }


        QTAILQ_FOREACH(port, &vser->ports, next) {
            send_control_event(vser, port->id, VIRTIO_CONSOLE_PORT_ADD, 1);
        }
        return;
    }

    port = find_port_by_id(vser, virtio_ldl_p(vdev, &gcpkt->id));
    if (!port) {
        error_report("virtio-serial-bus: Unexpected port id %u for device %s",
                     virtio_ldl_p(vdev, &gcpkt->id), vser->bus.qbus.name);
        return;
    }

    trace_virtio_serial_handle_control_message_port(port->id);

    vsc = VIRTIO_SERIAL_PORT_GET_CLASS(port);

    switch(cpkt.event) {
    case VIRTIO_CONSOLE_PORT_READY:
        if (!cpkt.value) {
            error_report("virtio-serial-bus: Guest failure in adding port %u for device %s",
                         port->id, vser->bus.qbus.name);
            break;
        }


        if (vsc->is_console) {
            send_control_event(vser, port->id, VIRTIO_CONSOLE_CONSOLE_PORT, 1);
        }

        if (port->name) {
            virtio_stl_p(vdev, &cpkt.id, port->id);
            virtio_stw_p(vdev, &cpkt.event, VIRTIO_CONSOLE_PORT_NAME);
            virtio_stw_p(vdev, &cpkt.value, 1);

            buffer_len = sizeof(cpkt) + strlen(port->name) + 1;
            buffer = g_malloc(buffer_len);

            memcpy(buffer, &cpkt, sizeof(cpkt));
            memcpy(buffer + sizeof(cpkt), port->name, strlen(port->name));
            buffer[buffer_len - 1] = 0;

            send_control_msg(vser, buffer, buffer_len);
            g_free(buffer);
        }

        if (port->host_connected) {
            send_control_event(vser, port->id, VIRTIO_CONSOLE_PORT_OPEN, 1);
        }


        if (vsc->guest_ready) {
            vsc->guest_ready(port);
        }
        break;

    case VIRTIO_CONSOLE_PORT_OPEN:
        port->guest_connected = cpkt.value;
        if (vsc->set_guest_connected) {

            vsc->set_guest_connected(port, cpkt.value);
        }
        break;
    }
}
