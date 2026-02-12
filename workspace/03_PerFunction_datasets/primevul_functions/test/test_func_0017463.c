modifiers2keycode(int modifiers, int *key, char_u *string)
{
    int new_slen = 0;

    if (modifiers != 0)
    {


	*key = simplify_key(*key, &modifiers);
	if (modifiers != 0)
	{
	    string[new_slen++] = K_SPECIAL;
	    string[new_slen++] = (int)KS_MODIFIER;
	    string[new_slen++] = modifiers;
	}
    }
    return new_slen;
}
