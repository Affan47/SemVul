bool parse_jfif_jpg( unsigned char type, unsigned int len, unsigned int alloc_len, unsigned char* segment )
{
    unsigned int hpos = 4;
    int lval, rval;
    int skip;
    int cmp;
    int i;


    switch ( type )
    {
        case 0xC4:

            while ( hpos < len ) {
                lval = LBITS( hpos < alloc_len ? segment[ hpos ] : 0, 4 );
                rval = RBITS( hpos < alloc_len ? segment[ hpos ]: 0, 4 );
                if ( ((lval < 0) || (lval >= 2)) || ((rval < 0) || (rval >= 4)) )
                    break;

                hpos++;

                if (!build_huffcodes( &(segment[ hpos + 0 ]), alloc_len > hpos ? alloc_len - hpos : 0,
                                      &(segment[ hpos + 16 ]),  alloc_len > hpos + 16 ? alloc_len - hpos - 16 : 0,
                                      &(hcodes[ lval ][ rval ]), &(htrees[ lval ][ rval ]) )) {
                    errorlevel.store(2);
                    return false;
                }
                htset[ lval ][ rval ] = 1;

                skip = 16;
                for ( i = 0; i < 16; i++ )
                    skip += ( int ) (hpos + i < alloc_len ? segment[ hpos + i ] : 0);
                hpos += skip;
            }

            if ( hpos != len ) {

                fprintf( stderr, "size mismatch in dht marker" );
                errorlevel.store(2);
                return false;
            }
            return true;

        case 0xDB:

            while ( hpos < len ) {
                lval = LBITS( hpos < alloc_len ? segment[ hpos ] :  0, 4 );
                rval = RBITS( hpos < alloc_len ? segment[ hpos ] : 0, 4 );
                if ( (lval < 0) || (lval >= 2) ) break;
                if ( (rval < 0) || (rval >= 4) ) break;
                hpos++;
                if ( lval == 0 ) {
                    for ( i = 0; i < 64; i++ ) {
                        qtables[ rval ][ i ] = ( unsigned short ) (hpos + i < alloc_len ? segment[ hpos + i ] : 0);
                        if ( qtables[ rval ][ i ] == 0 ) break;
                    }
                    hpos += 64;
                }
                else {
                    for ( i = 0; i < 64; i++ ) {
                        qtables[ rval ][ i ] =
                            B_SHORT( (hpos + (2*i)< alloc_len ? segment[ hpos + (2*i) ] : 0), (hpos + 2*i+1 < alloc_len?segment[ hpos + (2*i) + 1 ]:0) );
                        if ( qtables[ rval ][ i ] == 0 ) break;
                    }
                    hpos += 128;
                }
            }

            if ( hpos != len ) {

                fprintf( stderr, "size mismatch in dqt marker" );
                errorlevel.store(2);
                return false;
            }
            return true;

        case 0xDD:

          rsti = B_SHORT( hpos < alloc_len ? segment[ hpos ]:0, hpos +1 < alloc_len ?segment[ hpos + 1 ]:0 );
            return true;

        case 0xDA:

            cs_cmpc = hpos < alloc_len ? segment[ hpos ] : 0;
            if ( cs_cmpc > cmpc ) {
                fprintf( stderr, "%i components in scan, only %i are allowed",
                            cs_cmpc, cmpc );
                errorlevel.store(2);
                return false;
            }
            hpos++;
            for ( i = 0; i < cs_cmpc; i++ ) {
                for ( cmp = 0; ( (hpos < alloc_len ? segment[ hpos ]:0) != cmpnfo[ cmp ].jid ) && ( cmp < cmpc ); cmp++ );
                if ( cmp == cmpc ) {
                    fprintf( stderr, "component id mismatch in start-of-scan" );
                    errorlevel.store(2);
                    return false;
                }
                cs_cmp[ i ] = cmp;
                cmpnfo[ cmp ].huffdc = LBITS( hpos + 1< alloc_len ? segment[ hpos + 1 ]:0, 4 );
                cmpnfo[ cmp ].huffac = RBITS( hpos + 1 < alloc_len ? segment[ hpos + 1 ]:0, 4 );
                if ( ( cmpnfo[ cmp ].huffdc < 0 ) || ( cmpnfo[ cmp ].huffdc >= 4 ) ||
                     ( cmpnfo[ cmp ].huffac < 0 ) || ( cmpnfo[ cmp ].huffac >= 4 ) ) {
                    fprintf( stderr, "huffman table number mismatch" );
                    errorlevel.store(2);
                    return false;
                }
                hpos += 2;
            }
            cs_from = hpos < alloc_len ? segment[ hpos + 0 ]:0;
            cs_to   = hpos + 1 < alloc_len ? segment[ hpos + 1 ]:0;
            cs_sah  = LBITS( hpos + 2 < alloc_len ? segment[ hpos + 2 ]:0, 4 );
            cs_sal  = RBITS( hpos +2  <  alloc_len ? segment[ hpos + 2 ]:0, 4 );

            if ( ( cs_from > cs_to ) || ( cs_from > 63 ) || ( cs_to > 63 ) ) {
                fprintf( stderr, "spectral selection parameter out of range" );
                errorlevel.store(2);
                return false;
            }
            if ( ( cs_sah >= 12 ) || ( cs_sal >= 12 ) ) {
                fprintf( stderr, "successive approximation parameter out of range" );
                errorlevel.store(2);
                return false;
            }
            return true;

        case 0xC0:


        case 0xC1:


        case 0xC2:


            if ( type == 0xC2 )
                jpegtype = 2;
            else
                jpegtype = 1;


            lval = hpos < alloc_len ? segment[ hpos ]:0;
            if ( lval != 8 ) {
                fprintf( stderr, "%i bit data precision is not supported", lval );
                errorlevel.store(2);
                return false;
            }


            imgheight = B_SHORT( hpos +  1  < alloc_len ? segment[ hpos + 1 ]:0, hpos +  2 < alloc_len ?segment[ hpos + 2 ] :0);
            imgwidth  = B_SHORT( hpos + 3 < alloc_len ?segment[ hpos + 3 ]:0, hpos + 4 < alloc_len ?segment[ hpos + 4 ]:0 );
            cmpc      = hpos + 5 < alloc_len ?  segment[ hpos + 5 ]:0;
            if ( cmpc > 4 ) {
                cmpc = 4;
                fprintf( stderr, "image has %i components, max 4 are supported", cmpc );
                errorlevel.store(2);
                return false;
            }
            hpos += 6;

            for ( cmp = 0; cmp < cmpc; cmp++ ) {
                cmpnfo[ cmp ].jid = hpos < alloc_len ? segment[ hpos ]:0;
                cmpnfo[ cmp ].sfv = LBITS( hpos + 1 < alloc_len ? segment[ hpos + 1 ]:0, 4 );
                cmpnfo[ cmp ].sfh = RBITS( hpos + 1 < alloc_len ? segment[ hpos + 1 ]:0, 4 );
                if (cmpnfo[ cmp ].sfv > 4
                    || cmpnfo[ cmp ].sfh > 4) {
                    custom_exit(ExitCode::SAMPLING_BEYOND_FOUR_UNSUPPORTED);
                }
#ifndef ALLOW_3_OR_4_SCALING_FACTOR
                if (cmpnfo[ cmp ].sfv > 2
                    || cmpnfo[ cmp ].sfh > 2) {
                    custom_exit(ExitCode::SAMPLING_BEYOND_TWO_UNSUPPORTED);
                }
#endif
                uint32_t quantization_table_value = hpos + 2 < alloc_len ? segment[ hpos + 2 ]:0;
                if (quantization_table_value >= qtables.size()) {
                    errorlevel.store(2);
                    return false;
                }
                cmpnfo[ cmp ].qtable = qtables[quantization_table_value].begin();
                hpos += 3;
            }

            return true;

        case 0xC3:

            fprintf( stderr, "sof3 marker found, image is coded lossless" );
            errorlevel.store(2);
            return false;

        case 0xC5:

            fprintf( stderr, "sof5 marker found, image is coded diff. sequential" );
            errorlevel.store(2);
            return false;

        case 0xC6:

            fprintf( stderr, "sof6 marker found, image is coded diff. progressive" );
            errorlevel.store(2);
            return false;

        case 0xC7:

            fprintf( stderr, "sof7 marker found, image is coded diff. lossless" );
            errorlevel.store(2);
            return false;

        case 0xC9:

            fprintf( stderr, "sof9 marker found, image is coded arithm. sequential" );
            errorlevel.store(2);
            return false;

        case 0xCA:

            fprintf( stderr, "sof10 marker found, image is coded arithm. progressive" );
            errorlevel.store(2);
            return false;

        case 0xCB:

            fprintf( stderr, "sof11 marker found, image is coded arithm. lossless" );
            errorlevel.store(2);
            return false;

        case 0xCD:

            fprintf( stderr, "sof13 marker found, image is coded arithm. diff. sequential" );
            errorlevel.store(2);
            return false;

        case 0xCE:

            fprintf( stderr, "sof14 marker found, image is coded arithm. diff. progressive" );
            errorlevel.store(2);
            return false;

        case 0xCF:

            fprintf( stderr, "sof15 marker found, image is coded arithm. diff. lossless" );
            errorlevel.store(2);
            return false;

        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
        case 0xE8:
        case 0xE9:
        case 0xEA:
        case 0xEB:
        case 0xEC:
        case 0xED:
        case 0xEE:
        case 0xEF:
        case 0xFE:

            return true;

        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:

            fprintf( stderr, "rst marker found out of place" );
            errorlevel.store(2);
            return false;

        case 0xD8:

            fprintf( stderr, "soi marker found out of place" );
            errorlevel.store(2);
            return false;

        case 0xD9:

            fprintf( stderr, "eoi marker found out of place" );
            errorlevel.store(2);
            return false;

        default:

            fprintf( stderr, "unknown marker found: FF %2X", type );
            errorlevel.store(1);
            return true;
    }
}
