ins_compl_set_original_text(char_u *str)
{
    char_u	*p;


    if (match_at_original_text(compl_first_match))
    {
	p = vim_strsave(str);
	if (p != NULL)
	{
	    vim_free(compl_first_match->cp_str);
	    compl_first_match->cp_str = p;
	}
    }
    else if (compl_first_match->cp_prev != NULL
	    && match_at_original_text(compl_first_match->cp_prev))
    {
       p = vim_strsave(str);
       if (p != NULL)
       {
	   vim_free(compl_first_match->cp_prev->cp_str);
	   compl_first_match->cp_prev->cp_str = p;
       }
    }
}
