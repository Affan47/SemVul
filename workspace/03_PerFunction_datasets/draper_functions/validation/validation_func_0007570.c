RemoveContour( int iTarget )

{
    if( iTarget < nEntryCount )
        memmove( papoEntries + iTarget, papoEntries + iTarget + 1,
                 (nEntryCount - iTarget - 1) * sizeof(void*) );
    nEntryCount--;
}
