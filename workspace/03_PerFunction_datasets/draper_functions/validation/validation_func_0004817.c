get_handle_fn(ib_rpc_t rpc, int response)
{
	Smpfn *fn;

	if (response)
		return 0;

	if (rpc.mgtclass == IB_SMI_CLASS || rpc.mgtclass == IB_SMI_DIRECT_CLASS) {
		if (rpc.attr.id >= IB_ATTR_LAST
		    || !(fn = attrs[rpc.mgtclass & 0xf][rpc.attr.id]))
			return 0;
		return fn;
	}

	if (rpc.mgtclass == IB_PERFORMANCE_CLASS) {
		if (rpc.attr.id >= IB_GSI_ATTR_LAST
		    || !(fn = attrs[rpc.mgtclass & 0xf][rpc.attr.id]))
			return 0;
		return fn;
	}

	return 0;
}
