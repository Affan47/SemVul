in_csum(const uint16_t *addr, size_t len, uint32_t csum, uint32_t *acc)
{
	register size_t nleft = len;
	const uint16_t *w = addr;
	register uint16_t answer;
	register uint32_t sum = csum;


	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}


	if (nleft == 1)
		sum += htons(*(u_char *) w << 8);

	if (acc)
		*acc = sum;


	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = (~sum & 0xffff);
	return (answer);
}
