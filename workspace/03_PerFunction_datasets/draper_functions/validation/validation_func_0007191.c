extended_speeds_query(ib_portid_t * portid, int port, uint64_t ext_mask)
{
	int mask = ext_mask;

	if (!reset_only)
		common_func(portid, port, mask, 1, 0,
			    "PortExtendedSpeedsCounters",
			    IB_GSI_PORT_EXT_SPEEDS_COUNTERS,
			    mad_dump_port_ext_speeds_counters);

	if ((reset_only || reset) &&
	    !ext_speeds_reset_via(pc, portid, port, ext_mask, ibd_timeout, srcport))
		IBERROR("cannot reset PortExtendedSpeedsCounters");
}
