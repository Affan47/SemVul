Accept( TiXmlVisitor* visitor ) const
{
	if ( visitor->VisitEnter( *this, attributeSet.First() ) )
	{
		for ( const TiXmlNode* node=FirstChild(); node; node=node->NextSibling() )
		{
			if ( !node->Accept( visitor ) )
				break;
		}
	}
	return visitor->VisitExit( *this );
}
