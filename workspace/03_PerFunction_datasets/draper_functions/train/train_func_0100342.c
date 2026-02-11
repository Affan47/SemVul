getproduct(void)
{
	int type;
	long op;

	type = getorexpr();
	for (;;) {
		switch (gettoken()) {
		case T_MULT:	op = OP_MUL; break;
		case T_DIV:	op = OP_DIV; break;
		case T_MOD:	op = OP_MOD; break;
		case T_SLASHSLASH: op = OP_QUO; break;
		default:
			rescantoken();
			return type;
		}
		if (islvalue(type))
			addop(OP_GETVALUE);
		(void) getorexpr();
		addop(op);
		type = EXPR_RVALUE;
	}
}
