MergeJpegStreamingStatus merge_jpeg_streaming(MergeJpegProgress *stored_progress, const unsigned char * local_huff_data, unsigned int max_byte_coded,
                                              bool flush) {
    MergeJpegProgress progress(stored_progress);
    unsigned char SOI[ 2 ] = { 0xFF, 0xD8 };


    unsigned char  type = 0x00;

    if (progress.ipos == 0 && progress.hpos == 0 && progress.scan == 1 && progress.within_scan == false) {
        always_assert(max_file_size > grbs && "Lepton only supports files that have some scan data");
        str_out->set_bound(max_file_size - grbs);


        str_out->write( SOI, 2 );
    }


    while ( true )
    {
        if (!progress.within_scan) {
            progress.within_scan = true;

            unsigned int   tmp;
            tmp = progress.hpos;


            for ( type = 0x00; type != 0xDA; ) {
                if ( 3 + (uint64_t) progress.hpos >= hdrs ) break;
                type = hdrdata[ progress.hpos + 1 ];
                int len = 2 + B_SHORT( hdrdata[ progress.hpos + 2 ], hdrdata[progress.hpos + 3 ] );
                progress.hpos += len;
            }
            unsigned int actual_progress_hpos = std::min(progress.hpos, hdrs);

            str_out->write( hdrdata + tmp, ( actual_progress_hpos - tmp ) );
            for (unsigned int i = actual_progress_hpos; i < progress.hpos; ++i) {
                str_out->write("", 1);
            }
            if ((!g_use_seccomp) && post_byte == 0) {
                post_byte = clock();
            }


            if ( type != 0xDA ) break;


            progress.cpos = 0;
            progress.ipos = scnp.at(progress.scan - 1);
        }
        if ((int)progress.scan > scnc + 1) {
            break;
        }
        if (progress.ipos < max_byte_coded) {
            timing_operation_first_byte( 'd' );
        }

        unsigned int progress_ipos = progress.ipos;
        unsigned int progress_scan = scnp.at(progress.scan);
        unsigned int rstp_progress_rpos = rstp.empty() ? INT_MAX : rstp[ progress.rpos ];
        const unsigned char mrk = 0xFF;
        const unsigned char stv = 0x00;
        for ( ; progress_ipos & 0xf; progress_ipos++ ) {
            if (__builtin_expect(!(progress_ipos < max_byte_coded && (progress_scan == 0 || progress_ipos < progress_scan)), 0)) {
                break;
            }
            uint8_t byte_to_write = local_huff_data[progress_ipos];
            str_out->write_byte(byte_to_write);

            if (__builtin_expect(byte_to_write == 0xFF, 0))
                str_out->write_byte(stv);

            if (__builtin_expect(progress_ipos == rstp_progress_rpos, 0)) {
                if (rst_cnt_ok(progress.scan, progress.num_rst_markers_this_scan)) {
                    const unsigned char rst = 0xD0 + ( progress.cpos & 7);
                    str_out->write_byte(mrk);
                    str_out->write_byte(rst);
                    progress.rpos++; progress.cpos++;
                    rstp_progress_rpos = rstp.at(progress.rpos);
                    ++progress.num_rst_markers_this_scan;
                }
            }
        }

        while(true) {
            if (__builtin_expect(!(progress_ipos + 15 < max_byte_coded && (progress_scan == 0 || progress_ipos + 15 < progress_scan)), 0)) {
                break;
            }
            if ( __builtin_expect(aligned_memchr16ff(local_huff_data + progress_ipos)
                                  || (progress_ipos <= rstp_progress_rpos
                                      && progress_ipos + 15 >= rstp_progress_rpos), 0)){

                for (int veci = 0 ; veci < 16; ++veci, ++progress_ipos ) {
                    if (__builtin_expect(progress_ipos == rstp_progress_rpos, 0)) {
                        uint8_t byte_to_write = local_huff_data[progress_ipos];
                        str_out->write_byte(byte_to_write);

                        if (__builtin_expect(byte_to_write == 0xFF, 0)) {
                            str_out->write_byte(stv);
                        }
                        if (rst_cnt_ok(progress.scan, progress.num_rst_markers_this_scan)) {
                                const unsigned char rst = 0xD0 + ( progress.cpos & 7);
                                str_out->write_byte(mrk);
                                str_out->write_byte(rst);
                                progress.rpos++; progress.cpos++;
                                rstp_progress_rpos = rstp.at(progress.rpos);
                                ++progress.num_rst_markers_this_scan;
                        }
                    } else {
                        uint8_t byte_to_write = local_huff_data[progress_ipos];
                        str_out->write_byte(byte_to_write);

                        if (__builtin_expect(byte_to_write == 0xFF, 0)) {
                            str_out->write_byte(stv);
                        }
                    }
                }
            } else {
                str_out->write(local_huff_data + progress_ipos, 16);
                progress_ipos+=16;
            }
        }
        for ( ; ; progress_ipos++ ) {
            if (__builtin_expect(!(progress_ipos < max_byte_coded && (progress_scan == 0 || progress_ipos < progress_scan)), 0)) {
                break;
            }
            uint8_t byte_to_write = local_huff_data[progress_ipos];
            str_out->write_byte(byte_to_write);

            if (__builtin_expect(byte_to_write == 0xFF, 0))
                str_out->write_byte(stv);

            if (__builtin_expect(progress_ipos == rstp_progress_rpos, 0)) {
                if (rst_cnt_ok(progress.scan, progress.num_rst_markers_this_scan )) {
                    const unsigned char rst = 0xD0 + ( progress.cpos & 7);
                    str_out->write_byte(mrk);
                    str_out->write_byte(rst);
                    progress.rpos++; progress.cpos++;
                    rstp_progress_rpos = rstp.at(progress.rpos);
                    ++progress.num_rst_markers_this_scan;
                }
            }
        }
        progress.ipos = progress_ipos;
        if (scnp.at(progress.scan) == 0 && !flush) {
            return STREAMING_NEED_DATA;
        }
        if (progress.ipos >= max_byte_coded && progress.ipos != scnp.at(progress.scan) && !flush) {
            return STREAMING_NEED_DATA;
        }

        if (progress.scan - 1 < rst_err.size()) {
            while ( rst_err.at(progress.scan - 1) > 0 ) {
                const unsigned char rst = 0xD0 + ( progress.cpos & 7 );
                str_out->write_byte(mrk);
                str_out->write_byte(rst);
                progress.cpos++;    rst_err.at(progress.scan - 1)--;
            }
        }
        progress.num_rst_markers_this_scan = 0;
        progress.within_scan = false;

        progress.scan++;
        if(str_out->has_reached_bound()) {
            check_decompression_memory_bound_ok();
            break;
        }
    }


    str_out->set_bound(max_file_size);
    check_decompression_memory_bound_ok();

    if ( grbs > 0 )
        str_out->write( grbgdata, grbs );
    check_decompression_memory_bound_ok();
    str_out->flush();


    if ( str_out->chkerr() ) {
        fprintf( stderr, "write error, possibly drive is full" );
        errorlevel.store(2);
        return STREAMING_ERROR;
    }


    jpgfilesize = str_out->getsize();

    if (ujg_base_in) {
        ujgfilesize = ujg_base_in->getsize();
    } else {
        ujgfilesize = 4096 * 1024;
    }
#ifndef _WIN32

    if (!g_use_seccomp) {
        clock_t final = clock();
        struct timeval fin = {0,0};
        gettimeofday(&fin,NULL);
        double begin = current_operation_begin.tv_sec + (double)current_operation_begin.tv_usec / 1000000.;
        double end = fin.tv_sec + (double)fin.tv_usec / 1000000.;
        double first_byte = current_operation_first_byte.tv_sec + (double)current_operation_first_byte.tv_usec / 1000000.;
        double begin_to_end = end - begin;
        double begin_to_first_byte = begin_to_end;
        if (current_operation_first_byte.tv_sec != 0) {
            begin_to_first_byte = first_byte - begin;
        }

        fprintf(stderr, "TIMING (new method): %f to first byte %f total\n",
                begin_to_first_byte,
                begin_to_end);
        (void)final;


        fprintf(stderr, "Read took: %f\n",
                (read_done - overall_start)/(double)CLOCKS_PER_SEC);
    }
#endif
    return STREAMING_SUCCESS;

}
