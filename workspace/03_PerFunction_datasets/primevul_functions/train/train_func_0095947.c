decompileSETVARIABLE(int n, SWF_ACTION *actions,int maxn,int islocalvar)
{
	struct SWF_ACTIONPUSHPARAM *val, *var;

	val = pop();
	var = pop();
	if (val->Type!=12)
	{
		INDENT
	}
#ifdef DEBUG
	printf("*SETVariable* varName %s (type=%d)  valName=%s (type=%d)\n",
	       getName(var),var->Type, getName(val),val->Type);
#endif
	if (val->Type!=12 && islocalvar)
	{
		puts("var ");
	}
	if (gIndent<0)
	{
		puts(getName(var));
		return 0;
	}


	switch (val->Type)
	{
	case 10:
		puts(getName(var));
		printf(" = " );
		decompilePUSHPARAM(val,0);
		println(";");
		break;
	case 11:
		puts(getName(val));
		println(";");
		break;
	case 12:
		val->Type = PUSH_VARIABLE;
		break;
	default:
		puts(getName(var));
		printf(" = " );
		decompilePUSHPARAM(val,1);
		println(";");
	}
	return 0;
}
