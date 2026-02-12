void vnc_write(VncState *vs, const void *data, size_t len)
{
    assert(vs->magic == VNC_MAGIC);
    if (vs->disconnecting) {
        return;
    }


    if (vs->throttle_output_offset != 0 &&
        (vs->output.offset / VNC_THROTTLE_OUTPUT_LIMIT_SCALE) >
        vs->throttle_output_offset) {
        trace_vnc_client_output_limit(vs, vs->ioc, vs->output.offset,
                                      vs->throttle_output_offset);
        vnc_disconnect_start(vs);
        return;
    }
    buffer_reserve(&vs->output, len);

    if (vs->ioc != NULL && buffer_empty(&vs->output)) {
        if (vs->ioc_tag) {
            g_source_remove(vs->ioc_tag);
        }
        vs->ioc_tag = qio_channel_add_watch(
            vs->ioc, G_IO_IN | G_IO_OUT, vnc_client_io, vs, NULL);
    }

    buffer_append(&vs->output, data, len);
}
