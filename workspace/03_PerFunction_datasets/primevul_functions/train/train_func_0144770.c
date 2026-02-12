reg_getline(linenr_T lnum)
{


    if (rex.reg_firstlnum + lnum < 1)
	return NULL;
    if (lnum > rex.reg_maxline)

	return (char_u *)"";
    return ml_get_buf(rex.reg_buf, rex.reg_firstlnum + lnum, FALSE);
}
