ajDasSourceGetDBname(const AjPDasSource source, AjBool titleAndURI)
{
    AjPStr dbname = NULL;

    if (titleAndURI)
    {
	dbname = ajStrNewS(source->uri);

	ajStrAppendK(&dbname, '_');

	ajStrAppendS(&dbname, source->title);
    }
    else
	dbname = ajStrNewS(source->title);

    ajStrExchangeSetCC(&dbname, " \":+-()./", "_________");

    ajStrTrimC(&dbname, "_");

    ajStrTrimStartC(&dbname, "0123456789");

    return dbname;
}
