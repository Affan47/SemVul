activeMark( unsigned char *dest, MarkType type,
	int left, int top )
{
	Render::Mark mark = getMark( type );

	dest += getOffset( left, top, mark, 4 );

	int *p = (int *) dest;
	int skip = width-mark.getWidth();
	const char *src = mark.getPixels();

	for( int y = mark.getHeight(); y--; p += skip )
		for( int x = mark.getWidth(); x--; p++ )
			if( *(src++) )
				*p ^= 0xffffff;
}
