find_match(int lookfor, linenr_T ourscope)
{
    char_u	*look;
    pos_T	*theirscope;
    char_u	*mightbeif;
    int		elselevel;
    int		whilelevel;

    if (lookfor == LOOKFOR_IF)
    {
	elselevel = 1;
	whilelevel = 0;
    }
    else
    {
	elselevel = 0;
	whilelevel = 1;
    }

    curwin->w_cursor.col = 0;

    while (curwin->w_cursor.lnum > ourscope + 1)
    {
	curwin->w_cursor.lnum--;
	curwin->w_cursor.col = 0;

	look = cin_skipcomment(ml_get_curline());
	if (cin_iselse(look)
		|| cin_isif(look)
		|| cin_isdo(look)
		|| cin_iswhileofdo(look, curwin->w_cursor.lnum))
	{


	    theirscope = find_start_brace();
	    if (theirscope == NULL)
		break;


	    if (theirscope->lnum < ourscope)
		break;


	    if (theirscope->lnum > ourscope)
		continue;


	    look = cin_skipcomment(ml_get_curline());
	    if (cin_iselse(look))
	    {
		mightbeif = cin_skipcomment(look + 4);
		if (!cin_isif(mightbeif))
		    ++elselevel;
		continue;
	    }


	    if (cin_iswhileofdo(look, curwin->w_cursor.lnum))
	    {
		++whilelevel;
		continue;
	    }


	    look = cin_skipcomment(ml_get_curline());
	    if (cin_isif(look))
	    {
		elselevel--;


		if (elselevel == 0 && lookfor == LOOKFOR_IF)
		    whilelevel = 0;
	    }


	    if (cin_isdo(look))
		whilelevel--;


	    if (elselevel <= 0 && whilelevel <= 0)
		return OK;
	}
    }
    return FAIL;
}
