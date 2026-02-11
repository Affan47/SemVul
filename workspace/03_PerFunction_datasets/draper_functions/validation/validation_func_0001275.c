zmod_poly_2x2_mat_mul(zmod_poly_2x2_mat_t R, zmod_poly_2x2_mat_t A,
									                         zmod_poly_2x2_mat_t B)
{
	ulong min_A = FLINT_MIN(FLINT_MIN(A->a->length, A->b->length), FLINT_MIN(A->c->length, A->d->length));
   ulong min_B = FLINT_MIN(FLINT_MIN(B->a->length, B->b->length), FLINT_MIN(B->c->length, B->d->length));

	if ((R == A) || (R == B))
	{
		zmod_poly_2x2_mat_t T;
		zmod_poly_2x2_mat_init(T, A->a->p);

		if (FLINT_MIN(min_A, min_B) < ZMOD_POLY_2X2_STRASSEN_CUTOFF)
			zmod_poly_2x2_mat_mul_classical(T, A, B);
		else
         zmod_poly_2x2_mat_mul_strassen(T, A, B);

		zmod_poly_swap(T->a, R->a);
      zmod_poly_swap(T->b, R->b);
      zmod_poly_swap(T->c, R->c);
      zmod_poly_swap(T->d, R->d);

		zmod_poly_2x2_mat_clear(T);
	} else
	{
		if (FLINT_MIN(min_A, min_B) < ZMOD_POLY_2X2_STRASSEN_CUTOFF)
			zmod_poly_2x2_mat_mul_classical(R, A, B);
		else
         zmod_poly_2x2_mat_mul_strassen(R, A, B);
	}
}
