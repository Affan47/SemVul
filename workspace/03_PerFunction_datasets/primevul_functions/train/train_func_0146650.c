is_spotan_device(gx_device * dev)
{


    return dev->procs.open_device == san_open;
}
