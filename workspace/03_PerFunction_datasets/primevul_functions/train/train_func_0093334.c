bool recode_jpeg( void )
{
    if (!g_use_seccomp) {
        pre_byte = clock();
    }
    abitwriter*  huffw;
    abytewriter* storw;

    unsigned char  type = 0x00;
    unsigned int   len  = 0;
    unsigned int   hpos = 0;

    int lastdc[ 4 ];
    Sirikata::Aligned256Array1d<int16_t, 64> block;
    unsigned int eobrun;
    int rstw;

    int cmp, bpos, dpos;
    int mcu, sub, csc;
    int eob, sta;
    int tmp;


    huffw = new abitwriter( ABIT_WRITER_PRELOAD, max_file_size);
    huffw->fillbit = padbit;


    storw = new abytewriter( ABIT_WRITER_PRELOAD);


    scnc = 0;
    rstc = 0;
    MergeJpegProgress streaming_progress;


    while ( true )
    {

        for ( type = 0x00; type != 0xDA; ) {
            if ( hpos >= hdrs ) break;
            type = hpos + 1 < hdrs ? hdrdata[ hpos + 1 ] : 0;
            len = 2 + B_SHORT( hpos + 2 < hdrs ? hdrdata[ hpos + 2 ]:0, hpos + 3 < hdrs ? hdrdata[ hpos + 3 ] :0);
            if ( ( type == 0xC4 ) || ( type == 0xDA ) || ( type == 0xDD ) ) {
                if ( !parse_jfif_jpg( type, len, len > hdrs - hpos ? hdrs - hpos : len, &( hdrdata[ hpos ] ) ) ) {
                    delete huffw;
                    delete storw;
                    return false;
                }
                int max_scan = 0;
                for (int i = 0; i < cmpc; ++i) {
                    max_scan = std::max(max_scan, cmpnfo[i].bcv);
                }
                rstp.reserve(max_scan);
                scnp.reserve(max_scan);
                hpos += len;
            }
            else {
                hpos += len;
                continue;
            }
        }


        if ( type != 0xDA ) break;


        while ((int)scnp.size() < scnc + 2) {
            scnp.push_back(0);
        }


        if ( rsti > 0 ) {
            tmp = rstc + ( ( cs_cmpc > 1 ) ?
                ( mcuc / rsti ) : ( cmpnfo[ cs_cmp[ 0 ] ].bc / rsti ) );
            while ((int)rstp.size() <= tmp ) {
                rstp.push_back((unsigned int) -1 );
            }
        }


        cmp  = cs_cmp[ 0 ];
        csc  = 0;
        mcu  = 0;
        sub  = 0;
        dpos = 0;


        scnp.at(scnc) = huffw->getpos();
        scnp.at(scnc + 1) = 0;
        bool first_pass = true;

        while ( true )
        {

            lastdc[ 0 ] = 0;
            lastdc[ 1 ] = 0;
            lastdc[ 2 ] = 0;
            lastdc[ 3 ] = 0;


            sta = 0;


            eobrun = 0;


            rstw = rsti;
            if (cs_cmpc != colldata.get_num_components() && !g_allow_progressive) {
                custom_exit(ExitCode::PROGRESSIVE_UNSUPPORTED);
            }
            if (jpegtype != 1 && !g_allow_progressive) {
                custom_exit(ExitCode::PROGRESSIVE_UNSUPPORTED);
            }
            if ((jpegtype != 1 || cs_cmpc != colldata.get_num_components())
                && colldata.is_memory_optimized(0)
                && first_pass) {
                colldata.init(cmpnfo, cmpc, mcuh, mcuv, false);
            }
            first_pass = false;

            if ( cs_cmpc > 1 )
            {
                if ( jpegtype == 1 ) {

                    while ( sta == 0 ) {

                        const AlignedBlock &aligned_block = colldata.block((BlockType)cmp, dpos);

                        for ( bpos = 0; bpos < 64; bpos++ ) {
                            block[bpos] = aligned_block.coefficients_zigzag(bpos);
                        }
                        int16_t dc = block[0];

                        block[ 0 ] -= lastdc[ cmp ];
                        lastdc[ cmp ] = dc;


                        eob = encode_block_seq( huffw,
                                                &(hcodes[ 0 ][ cmpnfo[cmp].huffdc ]),
                                                &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                                                block.begin() );


                        if ( eob < 0 ) sta = -1;
                        else sta = next_mcupos( &mcu, &cmp, &csc, &sub, &dpos, &rstw, cs_cmpc);
                        if (sta == 0 && huffw->no_remainder()) {
                            merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                        }
                        if (str_out->has_exceeded_bound()) {
                            sta = 2;
                        }
                    }
                }
                else if ( cs_sah == 0 ) {


                    while ( sta == 0 ) {

                        tmp = colldata.at((BlockType)cmp , 0 , dpos ) >> cs_sal;
                        block[ 0 ] = tmp - lastdc[ cmp ];
                        lastdc[ cmp ] = tmp;


                        sta = encode_dc_prg_fs( huffw,
                                                &(hcodes[ 0 ][ cmpnfo[cmp].huffdc ]),
                                                block.begin() );


                        if ( sta != -1 )
                            sta = next_mcupos( &mcu, &cmp, &csc, &sub, &dpos, &rstw, cs_cmpc);
                        if (sta == 0 && huffw->no_remainder()) {
                            merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                        }
                        if (str_out->has_exceeded_bound()) {
                            sta = 2;
                        }
                    }
                }
                else {


                    while ( sta == 0 ) {

                        block[ 0 ] = BITN( colldata.at((BlockType)cmp , 0 , dpos ), cs_sal );


                        sta = encode_dc_prg_sa( huffw, block.begin() );


                        if ( sta != -1 )
                            sta = next_mcupos( &mcu, &cmp, &csc, &sub, &dpos, &rstw, cs_cmpc);
                        if (sta == 0 && huffw->no_remainder()) {
                            merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                        }
                        if (str_out->has_exceeded_bound()) {
                            sta = 2;
                        }

                    }
                }
            }
            else
            {
                if ( jpegtype == 1 ) {

                    while ( sta == 0 ) {
                        const AlignedBlock& aligned_block = colldata.block((BlockType)cmp, dpos);

                        int16_t dc = block[ 0 ] = aligned_block.dc();
                        for ( bpos = 1; bpos < 64; bpos++ )
                            block[ bpos ] = aligned_block.coefficients_zigzag(bpos);


                        block[ 0 ] -= lastdc[ cmp ];
                        lastdc[ cmp ] = dc;


                        eob = encode_block_seq( huffw,
                            &(hcodes[ 0 ][ cmpnfo[cmp].huffdc ]),
                            &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                                                block.begin() );


                        if ( eob < 0 ) sta = -1;
                        else sta = next_mcuposn( &cmp, &dpos, &rstw);
                        if (sta == 0 && huffw->no_remainder()) {
                            merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                        }
                        if (str_out->has_exceeded_bound()) {
                            sta = 2;
                        }

                    }
                }
                else if ( cs_to == 0 ) {
                    if ( cs_sah == 0 ) {


                        while ( sta == 0 ) {

                            tmp = colldata.at((BlockType)cmp , 0 , dpos ) >> cs_sal;
                            block[ 0 ] = tmp - lastdc[ cmp ];
                            lastdc[ cmp ] = tmp;


                            sta = encode_dc_prg_fs( huffw,
                                &(hcodes[ 0 ][ cmpnfo[cmp].huffdc ]),
                                                    block.begin() );


                            if ( sta != -1 )
                                sta = next_mcuposn( &cmp, &dpos, &rstw );
                            if (sta == 0 && huffw->no_remainder()) {
                                merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                            }
                            if (str_out->has_exceeded_bound()) {
                                sta = 2;
                            }

                        }
                    }
                    else {


                        while ( sta == 0 ) {

                            block[ 0 ] = BITN( colldata.at((BlockType)cmp , 0 , dpos ), cs_sal );


                            sta = encode_dc_prg_sa( huffw, block.begin() );


                            if ( sta != -1 )
                                sta = next_mcuposn( &cmp, &dpos, &rstw );
                        }
                        if (str_out->has_exceeded_bound()) {
                            sta = 2;
                        }
                    }
                }
                else {
                    if ( cs_sah == 0 ) {


                        while ( sta == 0 ) {
                            const AlignedBlock& aligned_block = colldata.block((BlockType)cmp, dpos);

                            for ( bpos = cs_from; bpos <= cs_to; bpos++ ) {
                                block[ bpos ] =
                                    FDIV2( aligned_block.coefficients_zigzag(bpos), cs_sal );
                            }

                            eob = encode_ac_prg_fs( huffw,
                                &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                                                    block.begin(), &eobrun, cs_from, cs_to );


                            if ( eob < 0 ) sta = -1;
                            else sta = next_mcuposn( &cmp, &dpos, &rstw );
                            if (sta == 0 && huffw->no_remainder()) {
                                merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                            }
                            if (str_out->has_exceeded_bound()) {
                                sta = 2;
                            }

                        }


                        encode_eobrun( huffw,
                            &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                            &eobrun );

                    }
                    else {


                        while ( sta == 0 ) {
                            const AlignedBlock& aligned_block= colldata.block((BlockType)cmp, dpos);

                            for ( bpos = cs_from; bpos <= cs_to; bpos++ ) {
                                block[ bpos ] =
                                    FDIV2( aligned_block.coefficients_zigzag(bpos), cs_sal );
                            }

                            eob = encode_ac_prg_sa( huffw, storw,
                                &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                                block.begin(), &eobrun, cs_from, cs_to );


                            if ( eob < 0 ) sta = -1;
                            else sta = next_mcuposn( &cmp, &dpos, &rstw );
                            if (sta == 0 && huffw->no_remainder()) {
                                merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
                            }
                            if (str_out->has_exceeded_bound()) {
                                sta = 2;
                            }

                        }


                        encode_eobrun( huffw,
                            &(hcodes[ 1 ][ cmpnfo[cmp].huffac ]),
                            &eobrun );


                        encode_crbits( huffw, storw );
                    }
                }
            }


            huffw->pad( padbit );


            if ( sta == -1 ) {
                fprintf( stderr, "encode error in scan%i / mcu%i",
                    scnc, ( cs_cmpc > 1 ) ? mcu : dpos );
                delete huffw;
                errorlevel.store(2);
                return false;
            }
            else if ( sta == 2 ) {
                scnc++;
                break;
            }
            else if ( sta == 1 ) {
                if ( rsti > 0 )
                    rstp.at(rstc++) = huffw->getpos() - 1;
            }
            huffw->flush_no_pad();
            dev_assert(huffw->no_remainder() && "this should have been padded");
            if (huffw->no_remainder()) {
                merge_jpeg_streaming(&streaming_progress, huffw->peekptr(), huffw->getpos(), false);
            }
        }
    }


    if ( huffw->error ) {
        delete huffw;
        fprintf( stderr, MEM_ERRMSG );
        errorlevel.store(2);
        return false;
    }


    huffdata = huffw->getptr();
    hufs = huffw->getpos();
    always_assert(huffw->no_remainder() && "this should have been padded");
    merge_jpeg_streaming(&streaming_progress, huffdata, hufs, true);
    if (!fast_exit) {
        delete huffw;


        delete storw;
    }

    if (scnc >= scnp.size()) {
        delete huffw;
        fprintf( stderr, MEM_ERRMSG );
        errorlevel.store(2);
        return false;
    }
    scnp.at(scnc) = hufs;
    if ( !rstp.empty() )
        rstp.at(rstc) = hufs;


    return true;
}
