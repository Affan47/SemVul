static inline bool addr4_match(__be32 a1, __be32 a2, u8 prefixlen)
{

	if (sizeof(long) == 4 && prefixlen == 0)
		return true;
	return !((a1 ^ a2) & htonl(~0UL << (32 - prefixlen)));
}
