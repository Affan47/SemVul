TIFF_description( FL_IMAGE * im )
{
    FILE *fp = im->fpin;
    SPEC *sp = fl_malloc( sizeof *sp );
    char buf[ 4 ];

    im->io_spec = sp;
    im->spec_size = sizeof *sp;
    sp->image = im;

    if ( fread( buf, 1, 4, fp ) != 4 )
    {
        flimage_error( im, "Failure to read TIFF file" );
        fl_free( sp );
        im->io_spec = NULL;
        im->spec_size = 0;
        return -1;
    }

    sp->endian = buf[ 0 ] == 'M' ? MSBFirst : LSBFirst;

    initialize_tiff_io( sp, sp->endian );

    sp->ifd_offset = sp->read4bytes( fp );

    if ( ! sp->ifd_offset )
    {
        flimage_error( im, "Invalid TIFF: no IFD" );
        fl_free( sp );
        im->io_spec = NULL;
        im->spec_size = 0;
        return -1;
    }

    read_tiff_ifd( fp, sp );

    if ( get_image_info_from_ifd( im ) < 0 )
    {
        fl_free( sp );
        im->io_spec = NULL;
        im->spec_size = 0;
        return -1;
    }

    return 0;
}
