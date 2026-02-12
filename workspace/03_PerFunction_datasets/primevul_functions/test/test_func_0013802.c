find_script_by_name(char_u *name)
{
    int		    sid;
    scriptitem_T    *si;

    for (sid = script_items.ga_len; sid > 0; --sid)
    {


	si = SCRIPT_ITEM(sid);
	if (si->sn_name != NULL && fnamecmp(si->sn_name, name) == 0)
	    return sid;
    }
    return -1;
}
