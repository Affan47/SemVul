dumpiov(tcp, len, addr)
struct tcb * tcp;
int len;
long addr;
{
#if defined(LINUX) && SUPPORTED_PERSONALITIES > 1
	union {
		struct { u_int32_t base; u_int32_t len; } *iov32;
		struct { u_int64_t base; u_int64_t len; } *iov64;
	} iovu;
#define iov iovu.iov64
#define sizeof_iov \
  (personality_wordsize[current_personality] == 4 \
   ? sizeof(*iovu.iov32) : sizeof(*iovu.iov64))
#define iov_iov_base(i) \
  (personality_wordsize[current_personality] == 4 \
   ? (u_int64_t) iovu.iov32[i].base : iovu.iov64[i].base)
#define iov_iov_len(i) \
  (personality_wordsize[current_personality] == 4 \
   ? (u_int64_t) iovu.iov32[i].len : iovu.iov64[i].len)
#else
	struct iovec *iov;
#define sizeof_iov sizeof(*iov)
#define iov_iov_base(i) iov[i].iov_base
#define iov_iov_len(i) iov[i].iov_len
#endif
	int i;
	unsigned long size;

	size = sizeof_iov * (unsigned long) len;
	if (size / sizeof_iov != len
	    || (iov = malloc(size)) == NULL) {
		fprintf(stderr, "out of memory\n");
		return;
	}
	if (umoven(tcp, addr, size, (char *) iov) >= 0) {
		for (i = 0; i < len; i++) {


			tprintf(" * %lu bytes in buffer %d\n",
				(unsigned long)iov_iov_len(i), i);
			dumpstr(tcp, (long) iov_iov_base(i),
				iov_iov_len(i));
		}
	}
	free((char *) iov);
#undef sizeof_iov
#undef iov_iov_base
#undef iov_iov_len
#undef iov
}
