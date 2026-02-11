format_special(void *record, char ** s, int tag) {
master_record_t *r 		  = (master_record_t *)record;
int	i, index;

	do_tag		  = tag;
	tag_string[0] = do_tag ? TAG_CHAR : '\0';
	tag_string[1] = '\0';

	duration = r->last - r->first;
	duration += ((double)r->msec_last - (double)r->msec_first) / 1000.0;
	for ( i=0; i<token_index; i++ ) {
		token_list[i].string_function(r, token_list[i].string_buffer);
	}


	i = 0;
	for ( index=0; index<format_index; index++ ) {
		int j = 0;
		while ( format_list[index][j] && i < STRINGSIZE )
			data_string[i++] = format_list[index][j++];
	}
	if ( i < STRINGSIZE )
		data_string[i] = '\0';

	data_string[STRINGSIZE-1] = '\0';
	*s = data_string;

}
