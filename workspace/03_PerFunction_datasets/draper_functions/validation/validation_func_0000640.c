fill_rand(void* buf, size_t size) {
	uint64_t var = 1, v;

	while (size >= 8) {
		var = var * FH_BC1 + 1;
		v = var ^ (var >> 32);
		memcpy(buf, &v, 8);
		size -= 8;
		buf += 8;
	}
}
