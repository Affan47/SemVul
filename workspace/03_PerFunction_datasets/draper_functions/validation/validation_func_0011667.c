doRound(PTW2_tableentry sortedtable[][n], int keybyte, int fixat, uint8_t fixvalue, int * searchborders, uint8_t * key, int keylen, PTW2_attackstate * state, uint8_t sum, int * strongbytes, int * bf, int validchars[][n]) {
	int i;
	uint8_t tmp;

	if (keybyte > 0) {
		if (!validchars[keybyte-1][key[keybyte-1]]) {
			return 0;
		}
	}
	if (keybyte == keylen) {
		return correct(state, key, keylen);
	} else if (bf[keybyte] == 1) {
		for (i = 0; i < n; i++) {
			key[keybyte] = i;
			if (doRound(sortedtable, keybyte+1, fixat, fixvalue, searchborders, key, keylen, state, sum+i%n, strongbytes, bf, validchars)) {
				return 1;
			}
		}
		return 0;
        } else if (keybyte == fixat) {
                key[keybyte] = fixvalue-sum;
                return doRound(sortedtable, keybyte+1, fixat, fixvalue, searchborders, key, keylen, state, fixvalue, strongbytes, bf, validchars);
	} else if (strongbytes[keybyte] == 1) {

		tmp = 3 + keybyte;
		for (i = keybyte-1; i >= 1; i--) {
			tmp += 3 + key[i] + i;
			key[keybyte] = n-tmp;
			if(doRound(sortedtable, keybyte+1, fixat, fixvalue, searchborders, key, keylen, state, (n-tmp+sum)%n, strongbytes, bf, validchars) == 1) {
				printf("hit with strongbyte for keybyte %d\n", keybyte);
				return 1;
			}
		}
		return 0;
	} else {
		for (i = 0; i < searchborders[keybyte]; i++) {
                    key[keybyte] = sortedtable[keybyte][i].b - sum;
                    if(!opt.is_quiet)
                    {
                        depth[keybyte] = i;
                        keytable[keybyte][i].b = key[keybyte];
                    }
                    if (doRound(sortedtable, keybyte+1, fixat, fixvalue, searchborders, key, keylen, state, sortedtable[keybyte][i].b, strongbytes, bf, validchars)) {
				return 1;
			}
		}
		return 0;
	}
}
