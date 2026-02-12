static int JPEGInitializeLibJPEG( TIFF * tif, int decompress )
{
    JPEGState* sp = JState(tif);

    if(sp->cinfo_initialized)
    {
        if( !decompress && sp->cinfo.comm.is_decompressor )
            TIFFjpeg_destroy( sp );
        else if( decompress && !sp->cinfo.comm.is_decompressor )
            TIFFjpeg_destroy( sp );
        else
            return 1;

        sp->cinfo_initialized = 0;
    }


    if ( decompress ) {
        if (!TIFFjpeg_create_decompress(sp))
            return (0);
    } else {
        if (!TIFFjpeg_create_compress(sp))
            return (0);
#ifndef TIFF_JPEG_MAX_MEMORY_TO_USE
#define TIFF_JPEG_MAX_MEMORY_TO_USE (10 * 1024 * 1024)
#endif


        if( sp->cinfo.c.mem->max_memory_to_use < TIFF_JPEG_MAX_MEMORY_TO_USE )
            sp->cinfo.c.mem->max_memory_to_use = TIFF_JPEG_MAX_MEMORY_TO_USE;
    }

    sp->cinfo_initialized = TRUE;

    return 1;
}
