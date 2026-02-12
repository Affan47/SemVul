is_valid_assembly_flags (guint32 flags) {

	flags &= ~(0x8000 | 0x4000);
	return ((flags == 1) || (flags == 0));
}
