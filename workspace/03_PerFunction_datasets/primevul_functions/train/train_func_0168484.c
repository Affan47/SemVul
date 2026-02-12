static int inflate_block(STATE_PARAM smallint *e)
{
	unsigned ll[286 + 30];
	unsigned t;
	unsigned b;
	unsigned k;


	b = gunzip_bb;
	k = gunzip_bk;


	b = fill_bitbuffer(PASS_STATE b, &k, 1);
	*e = b & 1;
	b >>= 1;
	k -= 1;


	b = fill_bitbuffer(PASS_STATE b, &k, 2);
	t = (unsigned) b & 3;
	b >>= 2;
	k -= 2;


	gunzip_bb = b;
	gunzip_bk = k;


	switch (t) {
	case 0:
	{
		unsigned n;
		unsigned b_stored;
		unsigned k_stored;


		b_stored = gunzip_bb;
		k_stored = gunzip_bk;


		n = k_stored & 7;
		b_stored >>= n;
		k_stored -= n;


		b_stored = fill_bitbuffer(PASS_STATE b_stored, &k_stored, 16);
		n = ((unsigned) b_stored & 0xffff);
		b_stored >>= 16;
		k_stored -= 16;

		b_stored = fill_bitbuffer(PASS_STATE b_stored, &k_stored, 16);
		if (n != (unsigned) ((~b_stored) & 0xffff)) {
			abort_unzip(PASS_STATE_ONLY);
		}
		b_stored >>= 16;
		k_stored -= 16;

		inflate_stored_setup(PASS_STATE n, b_stored, k_stored);

		return -1;
	}
	case 1:


	{
		int i;
		unsigned bl;
		unsigned bd;


		for (i = 0; i < 144; i++)
			ll[i] = 8;
		for (; i < 256; i++)
			ll[i] = 9;
		for (; i < 280; i++)
			ll[i] = 7;
		for (; i < 288; i++)
			ll[i] = 8;
		bl = 7;
		inflate_codes_tl = huft_build(ll, 288, 257, &lit, &bl);


		for (i = 0; i < 30; i++)
			ll[i] = 5;
		bd = 5;
		inflate_codes_td = huft_build(ll, 30, 0, &dist, &bd);


		inflate_codes_td = (void*)((uintptr_t)inflate_codes_td & ~(uintptr_t)1);


		inflate_codes_setup(PASS_STATE bl, bd);


		return -2;
	}
	case 2:
	{
		enum { dbits = 6 };
		enum { lbits = 9 };

		huft_t *td;
		unsigned i;
		unsigned j;
		unsigned l;
		unsigned m;
		unsigned n;
		unsigned bl;
		unsigned bd;
		unsigned nb;
		unsigned nl;
		unsigned nd;


		unsigned b_dynamic;
		unsigned k_dynamic;


		b_dynamic = gunzip_bb;
		k_dynamic = gunzip_bk;


		b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 5);
		nl = 257 + ((unsigned) b_dynamic & 0x1f);

		b_dynamic >>= 5;
		k_dynamic -= 5;
		b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 5);
		nd = 1 + ((unsigned) b_dynamic & 0x1f);

		b_dynamic >>= 5;
		k_dynamic -= 5;
		b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 4);
		nb = 4 + ((unsigned) b_dynamic & 0xf);

		b_dynamic >>= 4;
		k_dynamic -= 4;
		if (nl > 286 || nd > 30) {
			abort_unzip(PASS_STATE_ONLY);
		}


		for (j = 0; j < nb; j++) {
			b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 3);
			ll[border[j]] = (unsigned) b_dynamic & 7;
			b_dynamic >>= 3;
			k_dynamic -= 3;
		}
		for (; j < 19; j++)
			ll[border[j]] = 0;


		bl = 7;
		inflate_codes_tl = huft_build(ll, 19, 19, NULL, &bl);
		if (BAD_HUFT(inflate_codes_tl)) {
			abort_unzip(PASS_STATE_ONLY);
		}


		n = nl + nd;
		m = mask_bits[bl];
		i = l = 0;
		while ((unsigned) i < n) {
			b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, (unsigned)bl);
			td = inflate_codes_tl + ((unsigned) b_dynamic & m);
			j = td->b;
			b_dynamic >>= j;
			k_dynamic -= j;
			j = td->v.n;
			if (j < 16) {
				ll[i++] = l = j;
			} else if (j == 16) {
				b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 2);
				j = 3 + ((unsigned) b_dynamic & 3);
				b_dynamic >>= 2;
				k_dynamic -= 2;
				if ((unsigned) i + j > n) {
					abort_unzip(PASS_STATE_ONLY);
				}
				while (j--) {
					ll[i++] = l;
				}
			} else if (j == 17) {
				b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 3);
				j = 3 + ((unsigned) b_dynamic & 7);
				b_dynamic >>= 3;
				k_dynamic -= 3;
				if ((unsigned) i + j > n) {
					abort_unzip(PASS_STATE_ONLY);
				}
				while (j--) {
					ll[i++] = 0;
				}
				l = 0;
			} else {
				b_dynamic = fill_bitbuffer(PASS_STATE b_dynamic, &k_dynamic, 7);
				j = 11 + ((unsigned) b_dynamic & 0x7f);
				b_dynamic >>= 7;
				k_dynamic -= 7;
				if ((unsigned) i + j > n) {
					abort_unzip(PASS_STATE_ONLY);
				}
				while (j--) {
					ll[i++] = 0;
				}
				l = 0;
			}
		}


		huft_free(inflate_codes_tl);


		gunzip_bb = b_dynamic;
		gunzip_bk = k_dynamic;


		bl = lbits;
		inflate_codes_tl = huft_build(ll, nl, 257, &lit, &bl);
		if (BAD_HUFT(inflate_codes_tl)) {
			abort_unzip(PASS_STATE_ONLY);
		}
		bd = dbits;
		inflate_codes_td = huft_build(ll + nl, nd, 0, &dist, &bd);
		if (BAD_HUFT(inflate_codes_td)) {
			abort_unzip(PASS_STATE_ONLY);
		}


		inflate_codes_setup(PASS_STATE bl, bd);


		return -2;
	}
	default:
		abort_unzip(PASS_STATE_ONLY);
	}
}
