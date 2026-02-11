ReadAndLockBlock( int block_index,
                                     int win_xoff, int win_xsize )

{
    if( last_block_data == NULL )
        ThrowPCIDSKException( "ReadAndLockBlock() called on a file that is not pixel interleaved." );


    if( win_xoff == -1 && win_xsize == -1 )
    {
        win_xoff = 0;
        win_xsize = GetWidth();
    }

    if( win_xoff < 0 || win_xoff+win_xsize > GetWidth() )
    {
        ThrowPCIDSKException( "CPCIDSKFile::ReadAndLockBlock(): Illegal window - xoff=%d, xsize=%d",
                                   win_xoff, win_xsize );
    }

    if( block_index == last_block_index
        && win_xoff == last_block_xoff
        && win_xsize == last_block_xsize )
    {
        last_block_mutex->Acquire();
        return last_block_data;
    }


    FlushBlock();


    last_block_mutex->Acquire();

    ReadFromFile( last_block_data,
                  first_line_offset + block_index*block_size
                  + win_xoff * pixel_group_size,
                  pixel_group_size * win_xsize );
    last_block_index = block_index;
    last_block_xoff = win_xoff;
    last_block_xsize = win_xsize;

    return last_block_data;
}
