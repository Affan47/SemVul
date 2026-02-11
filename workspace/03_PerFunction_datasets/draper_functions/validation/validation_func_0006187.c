slapi_entry_next_attr( const Slapi_Entry *e, Slapi_Attr *prevattr, Slapi_Attr **attr )
{
	if ( e == NULL ) {
		return -1;
	}

	if ( prevattr == NULL ) {
		return -1;
	}

	*attr = prevattr->a_next;

	return ( *attr != NULL ) ? 0 : -1;
}
