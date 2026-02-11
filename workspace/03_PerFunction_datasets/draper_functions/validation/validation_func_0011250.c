modsin_detailr( xml *node, newstr *value )
{
	if ( node->value && node->value->len ) {
		if ( value->len ) newstr_addchar( value, ' ' );
		newstr_newstrcat( value, node->value );
	}
	if ( node->down ) modsin_detailr( node->down, value );
	if ( node->next ) modsin_detailr( node->next, value );
}
