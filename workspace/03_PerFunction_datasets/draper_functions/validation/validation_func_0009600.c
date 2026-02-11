draw_sprites( struct mame_bitmap *bitmap )
{
	int which;
	const data16_t *source = spriteram16;
	void (*drawtile)(
		struct mame_bitmap *,
		unsigned code,
		int color,
		int sx, int sy,
		int flipx, int flipy,
		int priority,
		int bShadow );
	data16_t sprite_control;
	data16_t ypos,tile,color,xpos;
	int priority;
	int width,height;
	int flipy,flipx;
	int row,col;
	int sx,sy;

	sprite_control = namcona1_vreg[0x22/2];
	if( sprite_control&1 ) source += 0x400;

	for( which=0; which<0x100; which++ )
	{
		ypos	= source[0];
		tile	= source[1];
		color	= source[2];
		xpos	= source[3];

		priority = pri_mask[color&0x7];
		width = ((color>>12)&0x3)+1;
		height = ((ypos>>12)&0x7)+1;
		flipy = ypos&0x8000;
		flipx = color&0x8000;

		if( (tile&0x8000)==0 )
		{
			drawtile = pdraw_masked_tile;
		}
		else
		{
			drawtile = pdraw_opaque_tile;
		}
		for( row=0; row<height; row++ )
		{
			sy = (ypos&0x1ff)-30+32;
			if( flipy )
			{
				sy += (height-1-row)*8;
			}
			else
			{
				sy += row*8;
			}
			for( col=0; col<width; col++ )
			{
				sx = (xpos&0x1ff)-10;
				if( flipx )
				{
					sx += (width-1-col)*8;
				}
				else
				{
					sx+=col*8;
				}
				drawtile(
					bitmap,
					tile + row*64+col,
					(color>>4)&0xf,
					((sx+16)&0x1ff)-8,
					((sy+8)&0x1ff)-8,
					flipx,flipy,
					priority,
					color&0x4000  );
			}
		}
		source += 4;
	}
}
