deskey (DES_KS k, unsigned char *key, int decrypt)
{
	unsigned char pc1m[56];
	unsigned char pcr[56];
	register int i,j,l;
	int m;
	unsigned char ks[8];

	for (j=0; j<56; j++) {
		l=pc1[j]-1;
		m = l & 07;
		pc1m[j]=(key[l>>3] &
			bytebit[m])
			? 1 : 0;
	}
	for (i=0; i<16; i++) {
		memset(ks,0,sizeof(ks));
		for (j=0; j<56; j++)
			pcr[j] = pc1m[(l=j+totrot[decrypt? 15-i : i])<(j<28? 28 : 56) ? l: l-28];

		for (j=0; j<48; j++){

			if (pcr[pc2[j]-1]){

				l= j % 6;
				ks[j/6] |= bytebit[l] >> 2;
			}
		}

		k[i][0] = ((guint32)ks[0] << 24)
		 | ((guint32)ks[2] << 16)
		 | ((guint32)ks[4] << 8)
		 | ((guint32)ks[6]);
		k[i][1] = ((guint32)ks[1] << 24)
		 | ((guint32)ks[3] << 16)
		 | ((guint32)ks[5] << 8)
		 | ((guint32)ks[7]);
	}
}
