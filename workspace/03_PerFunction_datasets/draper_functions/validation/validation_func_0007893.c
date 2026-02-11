better_next(lt_op_type lt,
    struct coord a0, struct coord b0, struct coord b)
{

	if (!lt(a0, b0))
		return 1;


	if (!lt(a0, b))
		return 0;


	if (lt(b, b0))
		return 1;


	if (lt(b0, b))
		return 0;


	if (lt == lt_xy)
		return 0;
	if (lt == lt_x)
		return closer(b.y-a0.y, b0.y-a0.y);
	if (lt == lt_y)
		return closer(b.x-a0.x, b0.x-a0.x);
	abort();
}
