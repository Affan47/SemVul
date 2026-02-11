roz_get_info( int tile_index,int which )
{
	data16_t tile;
	int bank;
	int mangle;


	tile = rozvideoram16[mRozPage[which]+tile_index];

	switch( namcos2_gametype )
	{
	case NAMCONB2_MACH_BREAKERS:
		bank = nth_byte16( &rozbank16[which*8/2], (tile>>11)&0x7 );
		tile = (tile&0x7ff)|(bank*0x800);
		mangle = tile;
		break;

	case NAMCONB2_OUTFOXIES:
		bank = nth_byte16( &rozbank16[which*8/2], (tile>>11)&0x7 );
		tile = (tile&0x7ff)|(bank*0x800);
		mangle = tile&~(0x50);

		if( tile&0x10 ) mangle |= 0x40;
		if( tile&0x40 ) mangle |= 0x10;
		break;

	case NAMCOS2_LUCKY_AND_WILD:
		mangle	= tile&0x01ff;
		tile &= 0x3fff;
		switch( tile>>9 )
		{
		case 0x00: mangle |= 0x1c00; break;
		case 0x01: mangle |= 0x0800; break;
		case 0x02: mangle |= 0x0000; break;

		case 0x08: mangle |= 0x1e00; break;
		case 0x09: mangle |= 0x0a00; break;
		case 0x0a: mangle |= 0x0200; break;

		case 0x10: mangle |= 0x2000; break;
		case 0x11: mangle |= 0x0c00; break;
		case 0x12: mangle |= 0x0400; break;

		case 0x18: mangle |= 0x2200; break;
		case 0x19: mangle |= 0x0e00; break;
		case 0x1a: mangle |= 0x0600; break;
		}
		break;

	case NAMCOS2_METAL_HAWK:
	default:
		mangle = tile&0x01ff;
		if( tile&0x1000 ) mangle |= 0x0200;
		if( tile&0x0200 ) mangle |= 0x0400;
		if( tile&0x0400 ) mangle |= 0x0800;
		if( tile&0x0800 ) mangle |= 0x1000;
		break;
	}
	SET_TILE_INFO( mRozGfxBank,mangle,0,0 );
	tile_info.mask_data = 32*tile + (UINT8 *)memory_region( mRozMaskRegion );
}
