grpParseEmbassy(AjPFile file, AjPStr* embassyname)
{

    AjPStr line = NULL;
    AjPStr text = NULL;

    AjPStrTok tokenhandle;
    char white[]     = " \t\n\r";
    char whiteplus[] = " \t\n\r:=";
    AjPStr tmpstr = NULL;
    AjPStr token  = NULL;
    AjPStr value  = NULL;
    ajint done = 0;

    ajStrAssignC(embassyname, "");


    while(ajReadlineTrim(file, &line))
    {
	grpNoComment(&line);

	if(ajStrGetLen(line))
	{
	    ajStrAppendS(&text, line);
	    ajStrAppendC(&text, " ");
	}
    }

    tokenhandle = ajStrTokenNewC(text, white);


    while(ajStrTokenNextParseC(tokenhandle, whiteplus, &tmpstr))
	if(ajStrPrefixCaseC(tmpstr, "application"))
	    break;


    ajStrTokenNextParseC(tokenhandle, white, &tmpstr);


    ajStrTokenNextParseC(tokenhandle, white, &tmpstr);
    if(ajStrCmpC(tmpstr, "[") == 0)
    {
	token=ajStrNew();


	while(ajStrTokenNextParseC(tokenhandle, whiteplus, &tmpstr))
	{
	    while(!ajStrMatchC(tmpstr, "]"))
	    {
		ajStrAssignS(&token, tmpstr);
		value = grpParseValueRB(tokenhandle, white);
		done = ajStrMatchC(value, "]");

		if(!done)
		{
		    ajStrTokenNextParseC(tokenhandle, whiteplus, &tmpstr);
		    ajStrFmtLower(&tmpstr);
		    done = ajStrMatchC(tmpstr, "]");
		}

		if(ajStrPrefixCaseC(token, "embassy"))
		{
		    ajStrAssignS(embassyname, value);
		}
	    }

	    if(done)
		break;
	}
    }

    ajStrDel(&tmpstr);
    ajStrDel(&line);
    ajStrDel(&text);
    ajStrTokenDel(&tokenhandle);

    return;
}
