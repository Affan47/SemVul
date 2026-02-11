vmsg_ignore(const gnutella_node_t *n, const struct vmsg *vmsg)
{
	if (GNET_PROPERTY(vmsg_debug)) {
		g_warning("VMSG got %s/%uv%u \"%s\" via %s, ignoring",
			vendor_code_to_string(vmsg->vendor),
			vmsg->id, vmsg->version, vmsg->name, node_infostr(n));
	}
}
