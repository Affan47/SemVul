init_apm_port(mca_btl_openib_device_t *device, int port, uint16_t lid)
{
    int index;
    struct mca_btl_openib_module_t *btl;
    for(index = 0; index < device->btls; index++) {
        btl = (mca_btl_openib_module_t *) opal_pointer_array_get_item(device->device_btls, index);


        btl->apm_port = port;
        btl->port_info.apm_lid = lid + btl->src_path_bits;
        mca_btl_openib_component.apm_ports++;
        BTL_VERBOSE(("APM-PORT: Setting alternative port - %d, lid - %d"
                    ,port ,lid));
    }
}
