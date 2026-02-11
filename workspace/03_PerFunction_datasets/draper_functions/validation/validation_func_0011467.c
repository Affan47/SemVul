SetAttribute( const char * cname, const char * cvalue )
{
	TIXML_STRING _name( cname );
	TIXML_STRING _value( cvalue );

	TiXmlAttribute* node = attributeSet.Find( _name );
	if ( node )
	{
		node->SetValue( cvalue );
		return;
	}

	TiXmlAttribute* attrib = new TiXmlAttribute( cname, cvalue );
	if ( attrib )
	{
		attributeSet.Add( attrib );
	}
	else
	{
		TiXmlDocument* document = GetDocument();
		if ( document ) document->SetError( TIXML_ERROR_OUT_OF_MEMORY, 0, 0, TIXML_ENCODING_UNKNOWN );
	}
}
