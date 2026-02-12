static bool stringAt(RCore *core, ut64 addr) {
	ut8 buf[32];
	r_io_read_at (core->io, addr - 1, buf, sizeof (buf));

	if (buf[0] != 0) {
		return false;
	}
	return is_string (buf + 1, 31, NULL);
}
