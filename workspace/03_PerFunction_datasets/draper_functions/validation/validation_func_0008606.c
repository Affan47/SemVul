show_hex_mem(int startbank, word32 start, int endbank, word32 end, int count)
{
	char	ascii[MAXNUM_HEX_PER_LINE];
	word32	i;
	int	val, offset;

	if(count < 0) {
		count = 16 - (start & 0xf);
	}

	offset = 0;
	ascii[0] = 0;
	printf("Showing hex mem: bank: %x, start: %x, end: %x\n",
		startbank, start, end);
	for(i = start; i <= end; i++) {
		if( (i==start) || (count == 16) ) {
			printf("%04x:",i);
		}
		printf(" %02x", get_memory_c((startbank <<16) + i, 0));
		val = get_memory_c((startbank << 16) + i, 0) & 0x7f;
		if(val < 32 || val >= 0x7f) {
			val = '.';
		}
		ascii[offset++] = val;
		ascii[offset] = 0;
		count--;
		if(count <= 0) {
			printf("   %s\n", ascii);
			offset = 0;
			ascii[0] = 0;
			count = 16;
		}
	}
	if(offset > 0) {
		printf("   %s\n", ascii);
	}
}
