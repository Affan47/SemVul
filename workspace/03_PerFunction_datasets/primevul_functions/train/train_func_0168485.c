static NOINLINE int inflate_codes(STATE_PARAM_ONLY)
{
	unsigned e;
	huft_t *t;

	if (resume_copy)
		goto do_copy;

	while (1) {
		bb = fill_bitbuffer(PASS_STATE bb, &k, bl);
		t = tl + ((unsigned) bb & ml);
		e = t->e;
		if (e > 16)
			do {
				if (e == 99) {
					abort_unzip(PASS_STATE_ONLY);
				}
				bb >>= t->b;
				k -= t->b;
				e -= 16;
				bb = fill_bitbuffer(PASS_STATE bb, &k, e);
				t = t->v.t + ((unsigned) bb & mask_bits[e]);
				e = t->e;
			} while (e > 16);
		bb >>= t->b;
		k -= t->b;
		if (e == 16) {
			gunzip_window[w++] = (unsigned char) t->v.n;
			if (w == GUNZIP_WSIZE) {
				gunzip_outbuf_count = w;

				w = 0;
				return 1;
			}
		} else {

			if (e == 15) {
				break;
			}


			bb = fill_bitbuffer(PASS_STATE bb, &k, e);
			nn = t->v.n + ((unsigned) bb & mask_bits[e]);
			bb >>= e;
			k -= e;


			bb = fill_bitbuffer(PASS_STATE bb, &k, bd);
			t = td + ((unsigned) bb & md);
			e = t->e;
			if (e > 16)
				do {
					if (e == 99) {
						abort_unzip(PASS_STATE_ONLY);
					}
					bb >>= t->b;
					k -= t->b;
					e -= 16;
					bb = fill_bitbuffer(PASS_STATE bb, &k, e);
					t = t->v.t + ((unsigned) bb & mask_bits[e]);
					e = t->e;
				} while (e > 16);
			bb >>= t->b;
			k -= t->b;
			bb = fill_bitbuffer(PASS_STATE bb, &k, e);
			dd = w - t->v.n - ((unsigned) bb & mask_bits[e]);
			bb >>= e;
			k -= e;


 do_copy:
			do {


				unsigned delta;

				dd &= GUNZIP_WSIZE - 1;
				e = GUNZIP_WSIZE - (dd > w ? dd : w);
				delta = w > dd ? w - dd : dd - w;
				if (e > nn) e = nn;
				nn -= e;


				if (delta >= e) {
					memcpy(gunzip_window + w, gunzip_window + dd, e);
					w += e;
					dd += e;
				} else {


					do {
						gunzip_window[w++] = gunzip_window[dd++];
					} while (--e);
				}
				if (w == GUNZIP_WSIZE) {
					gunzip_outbuf_count = w;
					resume_copy = (nn != 0);

					w = 0;
					return 1;
				}
			} while (nn);
			resume_copy = 0;
		}
	}


	gunzip_outbuf_count = w;
	gunzip_bb = bb;
	gunzip_bk = k;


	huft_free_all(PASS_STATE_ONLY);


	return 0;
}
