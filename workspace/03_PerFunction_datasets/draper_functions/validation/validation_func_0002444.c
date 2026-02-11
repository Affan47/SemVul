pcx_write_bitmap( char * real_filename, int w, int h, ubyte ** row_ptrs, ubyte * palette )
{
	int retval;
	int i;
	ubyte data;
	PCXHeader header;
	FILE * PCXfile;
	char filename[MAX_FILENAME_LEN];

	strcpy_s( filename, real_filename );
	char *p = strchr( filename, '.' );
	if ( p ) *p = 0;
	strcat_s( filename, ".pcx" );

	memset( &header, 0, sizeof( PCXHeader ) );

	header.Manufacturer = 10;
	header.Encoding = 1;
	header.Nplanes = 1;
	header.BitsPerPixel = 8;
	header.Version = 5;
	header.Xmax = (short)(w-1);
	header.Ymax = (short)(h-1);
	header.Ymin = 0;
	header.Xmin = 0;
	header.BytesPerLine =(short)(w);

	PCXfile = fopen( filename , "wb" );
	if ( !PCXfile )
		return PCX_ERROR_OPENING;

	if ( fwrite( &header, sizeof( PCXHeader ), 1, PCXfile ) != 1 )	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}

	for (i=0; i<h; i++ )	{
		if (!pcx_encode_line( row_ptrs[i], w, PCXfile ))	{
			fclose( PCXfile );
			return PCX_ERROR_WRITING;
		}
	}


	data = 12;
	if (fwrite( &data, 1, 1, PCXfile )!=1)	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}


	retval = fwrite( palette, 768, 1, PCXfile );


	if (retval !=1)	{
		fclose( PCXfile );
		return PCX_ERROR_WRITING;
	}

	fclose( PCXfile );
	return PCX_ERROR_NONE;

}
