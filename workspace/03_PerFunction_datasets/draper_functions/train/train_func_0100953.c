Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding _encoding )
{
	p = SkipWhiteSpace( p, _encoding );


	TiXmlDocument* document = GetDocument();
	if ( !p || !*p || !StringEqual( p, "<?xml-stylesheet", true, _encoding ) )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_DECLARATION, 0, 0, _encoding );
		return 0;
	}
	if ( data )
	{
		data->Stamp( p, _encoding );
		location = data->Cursor();
	}
	p += 5;

	type = "";
	href = "";

	while ( p && *p )
	{
		if ( *p == '>' )
		{
			++p;
			return p;
		}

		p = SkipWhiteSpace( p, _encoding );
		if ( StringEqual( p, "type", true, _encoding ) )
		{
			TiXmlAttribute attrib;
			p = attrib.Parse( p, data, _encoding );
			type = attrib.Value();
		}
		else if ( StringEqual( p, "href", true, _encoding ) )
		{
			TiXmlAttribute attrib;
			p = attrib.Parse( p, data, _encoding );
			href = attrib.Value();
		}
		else
		{

			while( p && *p && *p != '>' && !IsWhiteSpace( *p ) )
				++p;
		}
	}
	return 0;
}
