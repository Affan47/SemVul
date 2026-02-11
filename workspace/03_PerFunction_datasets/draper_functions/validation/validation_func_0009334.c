generate_lfn_chain(char *utf8name, LfnEntry_t *buf, BYTE checksum) {
	int res;
	int len;
	int i;
	int size;
	WORD lfn_name[256];

	memset(lfn_name, 0, 256*sizeof(WORD));
	len = res = utf8_strlen(utf8name);
	fprintf(stderr,"filename: %s, len:%d\n", utf8name, len);
	if ((res <= 0) || (res >255)) {
		perror("generate lfn chain() error: illegal filename length");
		return -1;
	}

	size = ((len -1) /13) +1;

	res = utf8to16(utf8name, lfn_name);
	if (res < 0)  {
		perror("utf8to16() error: illegal filename length %d");
		return -1;
	}


	memset(buf,0xFF, (21 * sizeof(LfnEntry_t)));


	for(i=0; i <len; i++) {
		res = set_lfn_char((LfnEntry_t *) &(buf[(size - 1 - (i / 13))]), lfn_name[i] , i);
		if (res != 0) return -1;
	}
	if ( (len % 13) != 0 ) {
		res = set_lfn_char((LfnEntry_t *) &(buf[0]), 0x0000 , (len % 13));
		if (res != 0) return -1;
	}

	for(i=1; i <=size; i++) {
		buf[size -i].LDIR_Ord = i;
		buf[size -i].LDIR_Attr = ATTR_LONG_NAME;
		buf[size -i].LDIR_Chksum = checksum;
		buf[size -i].LDIR_Type = 0;
		buf[size -i].LDIR_FstClusLO = 0;
	}

	buf[0].LDIR_Ord |= LFN_LASTENTRY;


	return ( size );
}
