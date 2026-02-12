bool read_jpeg(std::vector<std::pair<uint32_t,
                                     uint32_t>> *huff_input_offsets,
               input_byte_stream *jpg_in,
               Sirikata::Array1d<uint8_t, 2> header,
               bool is_embedded_jpeg){
    if (jpeg_embedding_offset) {
        prefix_grbs = jpeg_embedding_offset + 2;
        prefix_grbgdata = aligned_alloc(prefix_grbs);
        prefix_grbgdata[0] = header[0];
        prefix_grbgdata[1] = header[1];
        prefix_grbs = jpg_in->read(prefix_grbgdata + 2, jpeg_embedding_offset);
        always_assert((size_t)prefix_grbs == jpeg_embedding_offset);
    }
    std::vector<unsigned char> segment(1024);
    unsigned char  type = 0x00;
    unsigned int   len  = 0;
    unsigned int   crst = 0;
    unsigned int   cpos = 0;
    unsigned char  tmp;

    abytewriter* huffw;
    abytewriter* hdrw;
    abytewriter* grbgw;


    scnc = 0;

    hdrw = new abytewriter( 4096 );
    hdrs = 0;


    huffw = new abytewriter( 0 );
    hufs  = 0;


    while ( true ) {
        if ( type == 0xDA ) {

            cpos = 0;
            crst = 0;
            while ( true ) {
                huff_input_offsets->push_back(std::pair<uint32_t, uint32_t>(huffw->getpos(),
                                                                            jpg_in->getsize()));

                if ( jpg_in->read_byte( &tmp) == false ) {
                    early_eof(hdrw, huffw);
                    fprintf(stderr, "Early EOF\n");
                    break;
                }

                if ( tmp != 0xFF ) {
                    crst = 0;
                    while ( tmp != 0xFF ) {
                        huffw->write( tmp );
                        if ( jpg_in->read_byte( &tmp ) == false ) {
                            early_eof(hdrw, huffw);
                            break;
                        }
                    }
                }


                if ( tmp == 0xFF ) {
                    if ( jpg_in->read_byte( &tmp ) == false ) {
                        early_eof(hdrw, huffw);
                        break;
                    }
                    if ( tmp == 0x00 ) {
                        crst = 0;

                        huffw->write( 0xFF );
                        write_byte_bill(Billing::DELIMITERS, false, 1);
                    }
                    else if ( tmp == 0xD0 + ( cpos & 7 ) ) {

                        write_byte_bill(Billing::DELIMITERS, false, 2);
                        cpos++;
                        crst++;
                        while (rst_cnt.size() <= (size_t)scnc) {
                            rst_cnt.push_back(0);
                        }
                        ++rst_cnt.at(scnc);
                    }
                    else {

                        if((int)rst_err.size() < scnc) {
                            rst_err.insert(rst_err.end(), scnc - rst_err.size(), 0);
                        }
                        rst_err.push_back(crst);

                        scnc++;
                        always_assert(rst_err.size() == (size_t)scnc && "All reset errors must be accounted for");

                        segment[ 0 ] = 0xFF;
                        segment[ 1 ] = tmp;
                        break;
                    }
                }
                else {

                    break;
                }
            }
        }
        else {

            if ( jpg_in->read( segment.data(), 2 ) != 2 ) break;
            if ( segment[ 0 ] != 0xFF ) {

                fprintf( stderr, "size mismatch in marker segment FF %2X", type );
                errorlevel.store(2);
                if ( type == 0xFE ) {
                    if ( jpg_in->read( segment.data(), 1) != 1 ) break;
                    if ( segment[ 0 ] == 0xFF ) errorlevel.store(1);
                }
                if ( errorlevel.load() == 2 ) {
                    delete ( hdrw );
                    delete ( huffw );
                    return false;
                }
            }
        }


        type = segment[ 1 ];


        if ( type == EOI[1] ) {
            standard_eof(hdrw, huffw);

            break;
        }


        if ( jpg_in->read( segment.data() + 2, 2 ) != 2 ) break;
        len = 2 + B_SHORT( segment[ 2 ], segment[ 3 ] );
        if ( len < 4 ) break;


        segment.resize(len);


        if ( jpg_in->read( ( segment.data() + 4 ), ( len - 4 ) ) !=
            ( unsigned short ) ( len - 4 ) ) break;
        if (start_byte == 0 || is_needed_for_second_block(segment)) {
            hdrw->write_n( segment.data(), len );
        }
    }


    delete ( hdrw );
    delete ( huffw );


    if ( hdrs == 0 ) {
        fprintf( stderr, "unexpected end of data encountered in header" );
        errorlevel.store(2);
        return false;
    }
    if ( hufs == 0 ) {
        fprintf( stderr, "unexpected end of data encountered in huffman" );
        errorlevel.store(2);
        return false;
    }


    grbgw = new abytewriter( 1024 );
    unsigned char grb0 = jpg_in->get_penultimate_read();
    unsigned char grb1 = jpg_in->get_last_read();
    grbgw->write( grb0 );
    grbgw->write( grb1 );
    while( true ) {
        len = jpg_in->read( segment.data(), segment.size() );
        if ( len == 0 ) break;
        grbgw->write_n( segment.data(), len );
    }
    grbgdata = grbgw->getptr_aligned();
    grbs     = grbgw->getpos();
    delete ( grbgw );
    if (grbs == sizeof(EOI) && 0 == memcmp(grbgdata, EOI, sizeof(EOI))) {
        grbs = 0;
        aligned_dealloc(grbgdata);
        grbgdata = NULL;
    }


    jpgfilesize = jpg_in->getsize();


    if ( !setup_imginfo_jpg(false) ) {
        return false;
    }


    return true;
}
