mpz_addi_raw(mpz_ptr r, mpz_ptr z, mpz_atom_t *d, u_int32_t l)
{
	int err;
	u_int32_t maxi = MAX(z->l, l);
	mpz_atom_t car = 0;
	mpz_carry_t sum;
	u_int32_t j;
	mpz_atom_t *t = NULL;

	if (r->d == d) {
		if ((t = malloc(l*MPZ_ATOMSZ)) == NULL)
			return SBN_MEM;
		memcpy(t, d, l*MPZ_ATOMSZ);
		d = t;
	}

	if (r != z && ((err = mpz_zero_realloc(r, maxi)) != SBN_OK))
		return err;
	if ((err = mpz_realloc(z, (r == z) ? maxi : l)) != SBN_OK)
		return err;
	for(j = 0; j < l; j++) {
		sum = (mpz_carry_t) d[j] + z->d[j] + car;
		car = sum >> MPZ_SHIFT;
		sum &= MPZ_MASK;
		r->d[j] = sum;
	}
	for (j = l; j < z->l; j++) {
		sum = (mpz_carry_t) z->d[j] + car;
		car = sum >> MPZ_SHIFT;
		sum &= MPZ_MASK;
		r->d[j] = sum;
	}
	if (car) {
		r->d[j] = car;
		j++;
	}
	r->l = j;
	if (t)
		free(t);
	return SBN_OK;
}
