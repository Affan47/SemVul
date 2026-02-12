bool write_info( void )
{
    FILE* fp;
    const char* fn = "stdout";

    unsigned char  type = 0x00;
    unsigned int   len  = 0;
    unsigned int   hpos = 0;

    int cmp, bpos;
    int i;


    fp = stdout;
    if ( fp == NULL ){
        fprintf( stderr, FWR_ERRMSG, fn);
        errorlevel.store(2);
        return false;
    }


    fprintf( fp, "<Infofile for JPEG image:>\n\n\n");
    fprintf( fp, "coding process: %s\n", ( jpegtype == 1 ) ? "sequential" : "progressive" );

    fprintf( fp, "imageheight: %i / imagewidth: %i\n", imgheight, imgwidth );
    fprintf( fp, "component count: %i\n", cmpc );
    fprintf( fp, "mcu count: %i/%i/%i (all/v/h)\n\n", mcuc, mcuv, mcuh );


    fprintf( fp, "\nfile header structure:\n" );
    fprintf( fp, " type  length   hpos\n" );

    for ( hpos = 0; hpos < hdrs; hpos += len ) {
        type = hpos + 1 < hdrs ? hdrdata[ hpos + 1 ] : 0 ;
        len = 2 + B_SHORT( hpos  + 2 < hdrs ? hdrdata[ hpos + 2 ] : 0, hpos + 3 < hdrs ? hdrdata[ hpos + 3 ] : 0);
        fprintf( fp, " FF%2X  %6i %6i\n", type, len, hpos );
    }
    fprintf( fp, " _END       0 %6i\n", hpos );
    fprintf( fp, "\n" );


    for ( cmp = 0; cmp < cmpc; cmp++ ) {
        fprintf( fp, "\n" );
        fprintf( fp, "component number %i ->\n", cmp );
        fprintf( fp, "sample factors: %i/%i (v/h)\n", cmpnfo[cmp].sfv, cmpnfo[cmp].sfh );
        fprintf( fp, "blocks per mcu: %i\n", cmpnfo[cmp].mbs );
        fprintf( fp, "block count (mcu): %i/%i/%i (all/v/h)\n",
            cmpnfo[cmp].bc, cmpnfo[cmp].bcv, cmpnfo[cmp].bch );
        fprintf( fp, "block count (sng): %i/%i/%i (all/v/h)\n",
            cmpnfo[cmp].nc, cmpnfo[cmp].ncv, cmpnfo[cmp].nch );
        fprintf( fp, "quantiser table ->" );
        for ( i = 0; i < 64; i++ ) {
            bpos = zigzag[ i ];
            if ( ( i % 8 ) == 0 ) fprintf( fp, "\n" );
            fprintf( fp, "%4i, ", QUANT( cmp, bpos ) );
        }
        fprintf( fp, "\n" );
        fprintf( fp, "maximum values ->" );
        for ( i = 0; i < 64; i++ ) {
            bpos = zigzag[ i ];
            if ( ( i % 8 ) == 0 ) fprintf( fp, "\n" );
            fprintf( fp, "%4i, ", MAX_V( cmp, bpos ) );
        }
        fprintf( fp, "\n\n" );
    }


    fclose( fp );


    return true;
}
