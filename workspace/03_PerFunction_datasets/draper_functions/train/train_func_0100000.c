mc_queue_handle(uint32_t flags)
{
	struct xen_mc mc_op;
	int ret = 0;

	mc_op.cmd = XEN_MC_fetch;
	mc_op.interface_version = XEN_MCA_INTERFACE_VERSION;
	set_xen_guest_handle(mc_op.u.mc_fetch.data, &g_mi);
	do {
		mc_op.u.mc_fetch.flags = flags;
		ret = HYPERVISOR_mca(&mc_op);
		if (ret) {
			pr_err("Failed to fetch %surgent error log\n",
			       flags == XEN_MC_URGENT ? "" : "non");
			break;
		}

		if (mc_op.u.mc_fetch.flags & XEN_MC_NODATA ||
		    mc_op.u.mc_fetch.flags & XEN_MC_FETCHFAILED)
			break;
		else {
			ret = convert_log(&g_mi);
			if (ret)
				pr_warn("Failed to convert this error log, continue acking it anyway\n");

			mc_op.u.mc_fetch.flags = flags | XEN_MC_ACK;
			ret = HYPERVISOR_mca(&mc_op);
			if (ret) {
				pr_err("Failed to ack previous error log\n");
				break;
			}
		}
	} while (1);

	return ret;
}
