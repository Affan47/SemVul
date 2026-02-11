callk(int type, char *name, chainp args)
#endif
{
	register expptr p;

	p = mkexpr(OPCALL,
		(expptr)builtin(callk_kludge ? callk_kludge : type, name, 0),
		(expptr)args);
	p->exprblock.vtype = type;
	return(p);
}
