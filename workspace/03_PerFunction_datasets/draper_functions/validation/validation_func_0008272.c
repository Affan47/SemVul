nextaddr (uaecptr addr, uaecptr last, uaecptr *end)
{
	static uaecptr old;
	uaecptr paddr = addr;
	int next;
	if (last && 0) {
		if (addr >= last)
			return 0xffffffff;
		return addr + 1;
	}
	if (addr == 0xffffffff) {
		if (end)
			*end = currprefs.chipmem_size;
		return 0;
	}
	if (end)
		next = *end;
	addr = nextaddr2 (addr + 1, &next);
	if (end)
		*end = next;
	if (old != next) {
		if (addr != 0xffffffff)
			console_out_f (_T("Scanning.. %08x - %08x (%s)\n"), addr & 0xffffff00, next, get_mem_bank (addr).name);
		old = next;
	}
#if 0
	if (next && addr != 0xffffffff) {
		uaecptr xa = addr;
		if (xa == 1)
			xa = 0;
		console_out_f ("%08X -> %08X (%08X)...\n", xa, xa + next - 1, next);
	}
#endif
	return addr;
}
