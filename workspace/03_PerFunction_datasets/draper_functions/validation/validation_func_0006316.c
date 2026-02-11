single(int code, char *label, char *mnemo, char *oper)
{
	insert8(code);
	if (oper)
		error ("no operands allowed");
        return 0;
}
