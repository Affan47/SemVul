endxmlin_keyword( xml *node, fields *info )
{
	if ( xml_tagexact( node, "keyword" ) )
		endxmlin_data( node, "%K", info, 0 );
	if ( node->next )
		endxmlin_keyword( node->next, info );
}
