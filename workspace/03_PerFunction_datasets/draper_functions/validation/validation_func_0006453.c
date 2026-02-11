EC_GROUP_cmp(const EC_GROUP *a, const EC_GROUP *b, BN_CTX *ctx)
	{
	int    r = 0;
	BIGNUM *a1, *a2, *a3, *b1, *b2, *b3;
	BN_CTX *ctx_new = NULL;


	if (EC_METHOD_get_field_type(EC_GROUP_method_of(a)) !=
	    EC_METHOD_get_field_type(EC_GROUP_method_of(b)))
		return 1;

	if (EC_GROUP_get_curve_name(a) && EC_GROUP_get_curve_name(b) &&
	    EC_GROUP_get_curve_name(a) != EC_GROUP_get_curve_name(b))
		return 1;

	if (!ctx)
		ctx_new = ctx = BN_CTX_new();
	if (!ctx)
		return -1;

	BN_CTX_start(ctx);
	a1 = BN_CTX_get(ctx);
	a2 = BN_CTX_get(ctx);
	a3 = BN_CTX_get(ctx);
	b1 = BN_CTX_get(ctx);
	b2 = BN_CTX_get(ctx);
	b3 = BN_CTX_get(ctx);
	if (!b3)
		{
		BN_CTX_end(ctx);
		if (ctx_new)
			BN_CTX_free(ctx);
		return -1;
		}


	if (!a->meth->group_get_curve(a, a1, a2, a3, ctx) ||
	    !b->meth->group_get_curve(b, b1, b2, b3, ctx))
		r = 1;

	if (r || BN_cmp(a1, b1) || BN_cmp(a2, b2) || BN_cmp(a3, b3))
		r = 1;


	if (r || EC_POINT_cmp(a, EC_GROUP_get0_generator(a),
	    EC_GROUP_get0_generator(b), ctx))
		r = 1;

	if (!r)
		{

		if (!EC_GROUP_get_order(a, a1, ctx) ||
		    !EC_GROUP_get_order(b, b1, ctx) ||
		    !EC_GROUP_get_cofactor(a, a2, ctx) ||
		    !EC_GROUP_get_cofactor(b, b2, ctx))
			{
			BN_CTX_end(ctx);
			if (ctx_new)
				BN_CTX_free(ctx);
			return -1;
			}
		if (BN_cmp(a1, b1) || BN_cmp(a2, b2))
			r = 1;
		}

	BN_CTX_end(ctx);
	if (ctx_new)
		BN_CTX_free(ctx);

	return r;
	}
