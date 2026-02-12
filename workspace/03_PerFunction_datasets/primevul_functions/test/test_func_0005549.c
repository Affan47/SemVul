allow_64_bit(void)
{
#if defined(__x86_64__) || defined(__aarch64__)
	return 1;
#elif defined(__i386__) || defined(__i686__)


	if (in_protocol)
		return 1;
	return 0;
#else
	return 0;
#endif
}
