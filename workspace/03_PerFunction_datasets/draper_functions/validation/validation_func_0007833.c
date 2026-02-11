ex_tabmove(eap)
    exarg_T	*eap;
{
    int tab_number = 9999;

    if (eap->arg && *eap->arg != NUL)
    {
	char_u *p = eap->arg;
	int    relative = 0;


	if (*eap->arg == '-')
	{
	    relative = -1;
	    p = eap->arg + 1;
	}
	else if (*eap->arg == '+')
	{
	    relative = 1;
	    p = eap->arg + 1;
	}
	else
	    p = eap->arg;

	if (p == skipdigits(p))
	{

	    eap->errmsg = e_invarg;
	    return;
	}

	tab_number = getdigits(&p);
	if (relative != 0)
	    tab_number = tab_number * relative + tabpage_index(curtab) - 1;;
    }
    else if (eap->addr_count != 0)
	tab_number = eap->line2;

    tabpage_move(tab_number);
}
