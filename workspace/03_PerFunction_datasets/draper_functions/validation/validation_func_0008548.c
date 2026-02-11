bm_lock_tga( int handle, int bitmapnum, bitmap_entry *be, bitmap *bmp, ubyte bpp, ubyte flags )
{
	ubyte *data = NULL;
	int d_size, byte_size;
	char filename[MAX_FILENAME_LEN];


	bm_free_data( bitmapnum );

	if(Is_standalone){
		Assert(bpp == 8);
	}
	else
	{
		Assert( (bpp == 16) || (bpp == 24 ) || (bpp == 32) );
	}


	byte_size = (bpp >> 3);

	Assert( byte_size );
	Assert( be->mem_taken > 0 );

	data = (ubyte*)bm_malloc(bitmapnum, be->mem_taken);

	if (data) {
		memset( data, 0, be->mem_taken);
		d_size = byte_size;
 	} else {
		return;
 	}

	bmp->bpp = bpp;
	bmp->data = (ptr_u)data;
	bmp->palette = NULL;

	Assert( &be->bm == bmp );
#ifdef BMPMAN_NDEBUG
	Assert( be->data_size > 0 );
#endif

	int tga_error;


	EFF_FILENAME_CHECK;

	tga_error = targa_read_bitmap( filename, data, NULL, d_size, be->dir_type);

	if ( tga_error != TARGA_ERROR_NONE )	{
		bm_free_data( bitmapnum );
		return;
	}

	bmp->flags = 0;

	bm_convert_format( bitmapnum, bmp, bpp, flags );
}
