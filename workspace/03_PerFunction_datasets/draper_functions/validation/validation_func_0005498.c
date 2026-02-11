parse_num_blocks(const char *arg, int log_block_size)
{
	char *p;
	unsigned long long num;

	num = strtoull(arg, &p, 0);

	if (p[0] && p[1])
		return 0;

	switch (*p) {
	case 'T': case 't':
		num <<= 10;
	case 'G': case 'g':
		num <<= 10;
	case 'M': case 'm':
		num <<= 10;
	case 'K': case 'k':
		num >>= log_block_size;
		break;
	case 's':
		num >>= (1+log_block_size);
		break;
	case '\0':
		break;
	default:
		return 0;
	}
	return num;
}
