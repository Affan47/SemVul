featFindOutFormatC(const char* format, ajint* iformat)
{
    ajint i = 0;


    if(!*format)
	return ajFalse;

    ajStrAssignC(&featoutFormatTmp, format);
    ajStrFmtLower(&featoutFormatTmp);

    for(i=0; featOutFormat[i].Name; i++)
    {


	if(ajStrMatchC(featoutFormatTmp,
		       featOutFormat[i].Name))
	{
	    *iformat = i;
	    ajStrDelStatic(&featoutFormatTmp);


	    return ajTrue;
	}
    }


    ajStrDelStatic(&featoutFormatTmp);
    *iformat = 1;

    return ajFalse;
}
