NITFWriteTRE( VSILFILE* fp,
                         vsi_l_offset nOffsetUDIDL,
                         int  *pnOffset,
                         const char *pszTREName, char *pabyTREData, int nTREDataSize )

{
    char szTemp[12];
    int  nOldOffset;


    VSIFSeekL(fp, nOffsetUDIDL + 5, SEEK_SET);
    VSIFReadL(szTemp, 1, 5, fp);
    szTemp[5] = 0;
    nOldOffset = atoi(szTemp);

    if( nOldOffset == 0 )
    {
        nOldOffset = 3;
        PLACE(nOffsetUDIDL+10, IXSOFL, "000" );
        *pnOffset += 3;
    }

    if (nOldOffset + 11 + nTREDataSize > 99999 || nTREDataSize > 99999)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "Too big TRE to be written");
        return FALSE;
    }

    sprintf( szTemp, "%05d", nOldOffset + 11 + nTREDataSize );
    PLACE( nOffsetUDIDL + 5, IXSHDL, szTemp );


    sprintf( szTemp, "%-6s%05d",
             pszTREName, nTREDataSize );
    VSIFSeekL(fp, nOffsetUDIDL + 10 + nOldOffset, SEEK_SET);
    VSIFWriteL(szTemp, 11, 1, fp);
    VSIFWriteL(pabyTREData, nTREDataSize, 1, fp);


    *pnOffset += nTREDataSize + 11;

    return TRUE;
}
