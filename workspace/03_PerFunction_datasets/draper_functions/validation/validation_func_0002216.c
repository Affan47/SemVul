GetBlockSegment( int requested_block )

{
    if( requested_block < 0 )
        ThrowPCIDSKException( "SysVirtualFile::GetBlockSegment(%d) - illegal request.",
                              requested_block );

    if( requested_block >= blocks_loaded )
        LoadBMEntrysTo( requested_block );

    if( regular_blocks )

        return xblock_segment[0];
    else
        return xblock_segment[requested_block];
}
