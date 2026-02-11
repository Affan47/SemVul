FlushBlockBuf()

{
    CPLErr      eErr = CE_None;

    if( nLoadedBlock < 0 || !bLoadedBlockDirty )
        return CE_None;

    bLoadedBlockDirty = FALSE;

    if (!SetDirectory())
        return CE_Failure;

    eErr = WriteEncodedTileOrStrip(nLoadedBlock, pabyBlockBuf, TRUE);
    if (eErr != CE_None)
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                    "WriteEncodedTile/Strip() failed." );
        bWriteErrorInFlushBlockBuf = TRUE;
    }

    return eErr;
}
