process_sente( fields *info, char *p, int level )
{
	newstr link;
	newstr_init( &link );
	while ( *p && *p!=',' ) newstr_addchar( &link, *p++ );
	if ( link.len ) fields_add( info, "FILEATTACH", link.data, level );
	newstr_free( &link );
}
