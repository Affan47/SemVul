static huft_t* huft_build(const unsigned *b, const unsigned n,
			const unsigned s, const struct cp_ext *cp_ext,
			unsigned *m)
{
	unsigned a;
	unsigned c[BMAX + 1];
	unsigned eob_len;
	unsigned f;
	int g;
	int htl;
	unsigned i;
	unsigned j;
	int k;
	const unsigned *p;
	huft_t *q;
	huft_t r;
	huft_t *u[BMAX];
	unsigned v[N_MAX + 1];
	int ws[BMAX + 1];
	int w;
	unsigned x[BMAX + 1];
	unsigned *xp;
	int y;
	unsigned z;
	huft_t *result;
	huft_t **t;


	eob_len = n > 256 ? b[256] : BMAX;


	memset(c, 0, sizeof(c));
	p = b;
	i = n;
	do {
		c[*p]++;
		p++;
	} while (--i);
	if (c[0] == n) {
		q = xzalloc(3 * sizeof(*q));

		q[1].e = 99;
		q[1].b = 1;
		q[2].e = 99;
		q[2].b = 1;
		*m = 1;
		return q + 1;
	}


	for (j = 1; (j <= BMAX) && (c[j] == 0); j++)
		continue;
	k = j;
	for (i = BMAX; (c[i] == 0) && i; i--)
		continue;
	g = i;
	*m = (*m < j) ? j : ((*m > i) ? i : *m);


	for (y = 1 << j; j < i; j++, y <<= 1) {
		y -= c[j];
		if (y < 0)
			return ERR_RET;
	}
	y -= c[i];
	if (y < 0)
		return ERR_RET;
	c[i] += y;


	x[1] = j = 0;
	p = c + 1;
	xp = x + 2;
	while (--i) {
		j += *p++;
		*xp++ = j;
	}


	memset(v, 0xff, sizeof(v));
	p = b;
	i = 0;
	do {
		j = *p++;
		if (j != 0) {
			v[x[j]++] = i;
		}
	} while (++i < n);


	result = ERR_RET;
	t = &result;
	x[0] = i = 0;
	p = v;
	htl = -1;
	w = ws[0] = 0;
	u[0] = NULL;
	q = NULL;
	z = 0;


	for (; k <= g; k++) {
		a = c[k];
		while (a--) {


			while (k > ws[htl + 1]) {
				w = ws[++htl];


				z = g - w;
				z = z > *m ? *m : z;
				j = k - w;
				f = 1 << j;
				if (f > a + 1) {

					f -= a + 1;
					xp = c + k;
					while (++j < z) {
						f <<= 1;
						if (f <= *++xp) {
							break;
						}
						f -= *xp;
					}
				}
				j = (w + j > eob_len && w < eob_len) ? eob_len - w : j;
				z = 1 << j;
				ws[htl+1] = w + j;


				q = xzalloc((z + 1) * sizeof(huft_t));
				*t = q + 1;
				t = &(q->v.t);
				u[htl] = ++q;


				if (htl) {
					x[htl] = i;
					r.b = (unsigned char) (w - ws[htl - 1]);
					r.e = (unsigned char) (16 + j);
					r.v.t = q;
					j = (i & ((1 << w) - 1)) >> ws[htl - 1];
					u[htl - 1][j] = r;
				}
			}


			r.b = (unsigned char) (k - w);
			if (
			    *p == UINT_MAX
			) {
				r.e = 99;
			} else if (*p < s) {
				r.e = (unsigned char) (*p < 256 ? 16 : 15);
				r.v.n = (unsigned short) (*p++);
			} else {
				r.e = (unsigned char) cp_ext->ext[*p - s];
				r.v.n = cp_ext->cp[*p++ - s];
			}


			f = 1 << (k - w);
			for (j = i >> w; j < z; j += f) {
				q[j] = r;
			}


			for (j = 1 << (k - 1); i & j; j >>= 1) {
				i ^= j;
			}
			i ^= j;


			while ((i & ((1 << w) - 1)) != x[htl]) {
				w = ws[--htl];
			}
		}
	}


	*m = ws[1];

	if (y != 0 && g != 1)

		return (void*)((uintptr_t)result | 1);

	return result;
}
