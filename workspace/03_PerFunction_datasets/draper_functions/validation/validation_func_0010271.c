_is_fw_update_supported(int direct)
{


	if (is_z_remote()) {
		return 0;
	}

	if (ri.arch->firmware_base == 0
	    || (!direct && ri.arch->firmware_update_base == 0)
	    || (ri.arch->firmware_4847_offset == 0)) {
		return 0;
	}

	return 1;
}
