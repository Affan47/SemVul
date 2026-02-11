sig_isa_bus_outw(
	struct sig_isa_bus_main *b,
	void *s,
	unsigned short val,
	unsigned short port
)
{
	unsigned int nr;

	for (nr = 0; ; nr++) {
		if (nr == b->member_count) {
			return -1;
		}
		if (! b->member[nr].f->outw
		 || b->member[nr].s == s) {
			continue;
		}
		if (b->member[nr].f->outw(b->member[nr].s, val, port) == 0) {
			return 0;
		}
	}
}
