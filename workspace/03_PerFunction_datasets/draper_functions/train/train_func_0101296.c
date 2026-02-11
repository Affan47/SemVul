attrset(a)
	int	a;
{
	do_aend();
	if (a == A_BOLD)
	{
		do_MD();
		aend = ME;
	}
	else if (a == A_UNDERLINE)
	{
		do_US();
		aend = UE;
	}
	else if (a == A_ALTCHARSET)
	{
		do_AS();
		aend = AE;
	}
	else
	{
		aend = "";
	}
}
