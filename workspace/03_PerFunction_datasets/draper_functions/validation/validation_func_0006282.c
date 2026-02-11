center_put(int x1, int y1, int x2, int y2, const char* desStr, char clearBack)
{
	int tx = x1 + ((x2-x1+1) - text_width(desStr))/2;
	int ty = y1 + ((y2-y1+1) - font_height)/2;

	if( tx<0 )
		tx=0;

	if( clearBack && !Vga::use_back_buf && tx>x1 )
		vga_util.blt_buf( x1, y1, tx-1, y2, 0 );

	return put( tx, ty, desStr, clearBack, x2 );
}
