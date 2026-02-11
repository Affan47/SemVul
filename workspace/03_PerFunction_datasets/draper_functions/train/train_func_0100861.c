dump_daq_start (void* handle)
{
    DumpImpl* impl = (DumpImpl*)handle;
    const char* name = impl->name ? impl->name : DAQ_DUMP_FILE;
    pcap_t* pcap;
    int dlt;
    uint16_t snap;

    int ret = impl->module->start(impl->handle);

    if ( ret )
        return ret;

    dlt = impl->module->get_datalink_type(impl->handle);
    snap = impl->module->get_snaplen(impl->handle);

    pcap = pcap_open_dead(dlt, snap);

    impl->dump = pcap ? pcap_dump_open(pcap, name) : NULL;

    if ( !impl->dump )
    {
        impl->module->stop(impl->handle);
        impl->module->set_errbuf(impl->handle, "can't open dump file");
        return DAQ_ERROR;
    }
    pcap_close(pcap);
    return DAQ_SUCCESS;
}
