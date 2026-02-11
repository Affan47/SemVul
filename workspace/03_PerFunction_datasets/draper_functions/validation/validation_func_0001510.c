addgb18030char( newstr *s, unsigned int ch, int xmlout, int utf8out )
{
	unsigned char code[4];
	int nc, i;
	if ( xmlout ) {
		if ( minimalxmlchars( s, ch ) ) return;
		if ( ch > 127 && xmlout > 1 )
			{ addentity( s, ch ); return; }
	}
	nc = gb18030_encode( ch, code );
	for ( i=0; i<nc; ++i )
		newstr_addchar( s, code[i] );
}
