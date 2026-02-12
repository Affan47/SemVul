find_key_option(char_u *arg)
{
    int		key;
    int		modifiers;


    if (arg[0] == 't' && arg[1] == '_' && arg[2] && arg[3])
	key = TERMCAP2KEY(arg[2], arg[3]);
    else
    {
	--arg;
	modifiers = 0;
	key = find_special_key(&arg, &modifiers, TRUE, TRUE, FALSE);
	if (modifiers)
	    key = 0;
    }
    return key;
}
