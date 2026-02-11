Unpack_Track_2(UCHAR *b1, UCHAR *b2, USHORT pklen2, USHORT unpklen, UCHAR cmode, UCHAR flags){
	switch (cmode){
		case 0:

			memcpy(b2,b1,(size_t)unpklen);
			break;
		case 1:

			if (Unpack_RLE(b1,b2,unpklen)) return ERR_BADDECR;
			break;
		case 2:

			if (Unpack_QUICK(b1,b2,pklen2)) return ERR_BADDECR;
			if (Unpack_RLE(b2,b1,unpklen)) return ERR_BADDECR;
			memcpy(b2,b1,(size_t)unpklen);
			break;
		case 3:

			if (Unpack_MEDIUM(b1,b2,pklen2)) return ERR_BADDECR;
			if (Unpack_RLE(b2,b1,unpklen)) return ERR_BADDECR;
			memcpy(b2,b1,(size_t)unpklen);
			break;
		case 4:

			if (Unpack_DEEP(b1,b2,pklen2)) return ERR_BADDECR;
			if (Unpack_RLE(b2,b1,unpklen)) return ERR_BADDECR;
			memcpy(b2,b1,(size_t)unpklen);
			break;
		case 5:
		case 6:

			if (cmode==5) {

				if (Unpack_HEAVY(b1,b2,flags & 7,pklen2)) return ERR_BADDECR;
			} else {

				if (Unpack_HEAVY(b1,b2,flags | 8,pklen2)) return ERR_BADDECR;
			}
			if (flags & 4) {
				memset(b1,0,unpklen);

				if (Unpack_RLE(b2,b1,unpklen)) return ERR_BADDECR;
				memcpy(b2,b1,(size_t)unpklen);
			}
			break;
		default:
			return ERR_UNKNMODE;
	}

	if (!(flags & 1)) Init_Decrunchers();

	return NO_PROBLEM;

}
