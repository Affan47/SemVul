decompileEXTENDS(int n, SWF_ACTION *actions, int maxn)
{
	struct SWF_ACTIONPUSHPARAM *baseclass;

	baseclass=pop();
#if 0

	printf("class ");
	puts(getName(pop()));
	printf(" extends ");
	puts(getName(baseclass));
	println(" {" );
#else

	println("asm {");
	println(" push '%s'", getName(pop()));
	println(" getvariable");
	println(" push '%s'", getName(baseclass));
	println(" getvariable");
	println(" extends");
	println("};");
#endif

	return 0;
}
}
