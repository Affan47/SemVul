process_compflags(
    spellinfo_T	*spin,
    afffile_T	*aff,
    char_u	*compflags)
{
    char_u	*p;
    char_u	*prevp;
    unsigned	flag;
    compitem_T	*ci;
    int		id;
    int		len;
    char_u	*tp;
    char_u	key[AH_KEY_LEN];
    hashitem_T	*hi;


    len = (int)STRLEN(compflags) + 1;
    if (spin->si_compflags != NULL)
	len += (int)STRLEN(spin->si_compflags) + 1;
    p = getroom(spin, len, FALSE);
    if (p == NULL)
	return;
    if (spin->si_compflags != NULL)
    {
	STRCPY(p, spin->si_compflags);
	STRCAT(p, "/");
    }
    spin->si_compflags = p;
    tp = p + STRLEN(p);

    for (p = compflags; *p != NUL; )
    {
	if (vim_strchr((char_u *)"/?*+[]", *p) != NULL)

	    *tp++ = *p++;
	else
	{

	    prevp = p;
	    flag = get_affitem(aff->af_flagtype, &p);
	    if (flag != 0)
	    {


		vim_strncpy(key, prevp, p - prevp);
		hi = hash_find(&aff->af_comp, key);
		if (!HASHITEM_EMPTY(hi))
		    id = HI2CI(hi)->ci_newID;
		else
		{
		    ci = (compitem_T *)getroom(spin, sizeof(compitem_T), TRUE);
		    if (ci == NULL)
			break;
		    STRCPY(ci->ci_key, key);
		    ci->ci_flag = flag;


		    do
		    {
			check_renumber(spin);
			id = spin->si_newcompID--;
		    } while (vim_strchr((char_u *)"/?*+[]\\-^", id) != NULL);
		    ci->ci_newID = id;
		    hash_add(&aff->af_comp, ci->ci_key);
		}
		*tp++ = id;
	    }
	    if (aff->af_flagtype == AFT_NUM && *p == ',')
		++p;
	}
    }

    *tp = NUL;
}
