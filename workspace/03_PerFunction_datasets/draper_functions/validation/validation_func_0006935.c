getRangeMin(char * addrPacked, int prefix) {
    char packed[16];
    char mask;
    memcpy(packed, addrPacked,16);
    if (prefix%8!=0) {
	mask = bitMask[prefix%8];
	packed[prefix/8] = packed[prefix/8] & mask;
	prefix = (prefix/8 + 1)*8;
    }
    for (int i=prefix/8;i<16; i++) {
	packed[i]=0;
    }
    return new TIPv6Addr(packed, false);
}
