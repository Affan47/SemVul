output_item( fields *info, FILE *outptr, char *tag, int item, int level )
{
	int i;
	if ( item==-1 ) return;
	for ( i=0; i<level; ++i ) fprintf( outptr, " " );
	fprintf( outptr, "<%s>%s</%s>\n", tag, info->data[item].data, tag );
	fields_setused( info, item );
}
