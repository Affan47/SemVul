embBtreeParseEmblDe(const AjPStr readline, EmbPBtreeField field)
{
    AjPStr str = NULL;

    ajStrAssignSubS(&embindexLine, readline, 5, -1);

    ajStrTokenAssignC(&embindexHandle,embindexLine,"\n\r \t()");

    while(ajStrTokenNextParse(embindexHandle,&embindexToken))
    {
	ajStrTrimWhite(&embindexToken);
	ajStrTrimEndC(&embindexToken,".,:;'\"");
	ajStrTrimStartC(&embindexToken,"'\"");

	if(ajStrGetLen(embindexToken))
	{
            if(field->freecount)
                str = field->freelist[--field->freecount];

            ajStrAssignS(&str, embindexToken);

	    ajListstrPushAppend(field->data, str);
	    str = NULL;
	}
    }

    return;
}
