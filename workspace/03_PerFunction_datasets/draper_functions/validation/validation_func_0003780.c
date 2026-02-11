f_decode (size_t z, unsigned char *bz, size_t n, unsigned char *bp)
{


	if        (CP_SCHEME == CP1) {


		return huff_decode (bz, z, bp, &n, MAXBLOCK);

	} else if (CP_SCHEME == CP2) {


		return lzf_decode  (bz, z, bp, &n, MAXBLOCK);

	} else if (CP_SCHEME == CP3) {


		return zlib_decode (bz, z, bp, &n, MAXBLOCK);

	} else if (CP_SCHEME == CP4) {


		return lzma_decode (bz, z, bp, &n, n);

	} else if (CP_SCHEME == CP7) {


		return rle_decode (bz, z, bp, &n, MAXBLOCK);

	#if defined (LIBBZIP2)
	} else if (CP_SCHEME == CP8) {


		return bzip2_decode (bz, z, bp, &n, MAXBLOCK);
	#endif

	} else if (CP_SCHEME == CP9) {

		return justcopy_decode (bz, z, bp, &n, MAXBLOCK);

	} else {

		return FALSE;
	}
}
