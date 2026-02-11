acceptvalue(VALUE *v1, VALUE *v2)
{
	long index;
	FUNC *fp;
	BOOL ret;

	index = adduserfunc("accept");
	fp = findfunc(index);
	if (fp) {
		++stack;
		stack->v_type = V_ADDR;
		stack->v_subtype = V_NOSUBTYPE;
		stack->v_addr = v1;
		++stack;
		stack->v_type = V_ADDR;
		stack->v_subtype = V_NOSUBTYPE;
		stack->v_addr = v2;
		calculate(fp, 2);
		ret = testvalue(stack);
		freevalue(stack--);
		return ret;
	}
	return (!comparevalue(v1, v2));
}
