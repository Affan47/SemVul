latex2char( char *s, unsigned int *pos, int *unicode )
{
	unsigned int value;
	char *p, *q[3];
	int i, j, l[3];
	p = &( s[*pos] );
	value = (unsigned char) *p;
	if ( value=='{' || value=='\\' || value=='~' ||
	     value=='$' || value=='\'' || value=='`' ||
	     value=='-' || value=='^' ) {
		for ( i=0; i<nlatex_chars; ++i ) {
			q[0] = latex_chars[i].bib1;
			l[0] = strlen( q[0] );
			q[1] = latex_chars[i].bib2;
			l[1] = strlen( q[1] );
			q[2] = latex_chars[i].bib3;
			l[2] = strlen( q[2] );
			for ( j=0; j<3; ++j ) {
				if ( l[j] && !strncmp( p, q[j], l[j] ) ) {
					*pos = *pos + l[j];
					*unicode = 1;
					return latex_chars[i].unicode;
				}
			}
		}
	}
	*unicode = 0;
	*pos = *pos + 1;
	return value;
}
