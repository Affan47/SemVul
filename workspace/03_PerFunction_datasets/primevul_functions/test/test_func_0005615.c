proto_reg_handoff_sysdig_event(void)
{
    dissector_handle_t sysdig_event_handle;


    sysdig_event_handle = create_dissector_handle(dissect_sysdig_event,
            proto_sysdig_event);
    dissector_add_uint("pcapng.block_type", BLOCK_TYPE_SYSDIG_EVENT, sysdig_event_handle);
    dissector_add_uint("pcapng.block_type", BLOCK_TYPE_SYSDIG_EVENT_V2, sysdig_event_handle);
    dissector_add_uint("pcapng.block_type", BLOCK_TYPE_SYSDIG_EVENT_V2_LARGE, sysdig_event_handle);
}
