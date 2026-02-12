spice_server_char_device_add_interface(SpiceServer *reds, SpiceBaseInstance *sin)
{
    SpiceCharDeviceInstance* char_device =
            SPICE_UPCAST(SpiceCharDeviceInstance, sin);
    red::shared_ptr<RedCharDevice> dev_state;

    spice_debug("CHAR_DEVICE %s", char_device->subtype);
    if (strcmp(char_device->subtype, SUBTYPE_VDAGENT) == 0) {
        if (reds->vdagent) {
            spice_warning("vdagent already attached");
            return -1;
        }
        dev_state = attach_to_red_agent(reds, char_device);
    }
#ifdef USE_SMARTCARD
    else if (strcmp(char_device->subtype, SUBTYPE_SMARTCARD) == 0) {
        dev_state = smartcard_device_connect(reds, char_device);
        if (!dev_state) {
            return -1;
        }
    }
#endif
    else if (strcmp(char_device->subtype, SUBTYPE_USBREDIR) == 0) {
        dev_state = spicevmc_device_connect(reds, char_device, SPICE_CHANNEL_USBREDIR);
    }
    else if (strcmp(char_device->subtype, SUBTYPE_PORT) == 0) {
        if (strcmp(char_device->portname, "org.spice-space.webdav.0") == 0) {
            dev_state = spicevmc_device_connect(reds, char_device, SPICE_CHANNEL_WEBDAV);
        } else if (strcmp(char_device->portname, "org.spice-space.stream.0") == 0) {
            dev_state = stream_device_connect(reds, char_device);
        } else {
            dev_state = spicevmc_device_connect(reds, char_device, SPICE_CHANNEL_PORT);
        }
    }

    if (dev_state) {


        spice_assert(dev_state.get() == char_device->st);


        if (reds->vm_running) {
            dev_state->start();
        }
        reds_add_char_device(reds, dev_state);
    } else {
        spice_warning("failed to create device state for %s", char_device->subtype);
        return -1;
    }
    return 0;
}
