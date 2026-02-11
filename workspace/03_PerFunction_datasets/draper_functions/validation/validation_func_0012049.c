embBtreeGenBankTX(const AjPStr kwline, AjPList kwlist, ajuint maxlen)
{
    AjPStr token     = NULL;
    AjPStr str       = NULL;

    ajStrAssignSubS(&embindexLine, kwline, 9, -1);

    ajStrTokenAssignC(&embindexHandle,embindexLine,"\n\r;()");

    while(ajStrTokenNextParse(embindexHandle,&token))
    {
	ajStrTrimEndC(&token,".");
	ajStrTrimEndC(&token," ");
	ajStrTrimWhite(&token);

	if(ajStrGetLen(token))
	{
	    if(maxlen)
	    {
		if(ajStrGetLen(token) > maxlen)
		    ajStrAssignSubS(&str,token,0,maxlen-1);
		else
		    ajStrAssignS(&str,token);

	    }
	    else
		ajStrAssignS(&str,token);

	    ajListstrPushAppend(kwlist, str);
	    str = NULL;
	}
    }

    ajStrDel(&token);

    return;
}
