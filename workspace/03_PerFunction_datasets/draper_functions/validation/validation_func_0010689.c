Close()
{
    if( !out )
        return;


    streambuf* sb = out->rdbuf();
    delete out;
    delete sb;
    out = 0;


    int err = Z_OK;
    while( err == Z_OK
           && ( err = deflate( &zs, Z_FINISH )) == Z_OK )
    {
        zip.write( cbuf, sizeof(cbuf) );
        zs.next_out = (Bytef*)cbuf;
        zs.avail_out = sizeof(cbuf);
    }
    if( err == Z_STREAM_END ) {
        zip.write( cbuf, sizeof(cbuf)-zs.avail_out );
    } else {
        cerr << "zip error" << endl;
        exit( -1 );
    }
    if( deflateEnd( &zs ) != Z_OK ) {
        cerr << "deflateEnd" << endl;
        exit( -1 );
    }

    fileinfo& fi = fileinfos.back();
    fi.uncompressed_size = zs.total_in;
    fi.compressed_size = zs.total_out;


    write4( zip, fi.crc32 );
    write4( zip, fi.uncompressed_size );
    write4( zip, fi.compressed_size );
}
