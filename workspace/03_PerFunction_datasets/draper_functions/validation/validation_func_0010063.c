NITFReadBLOCKA_GCPs( NITFImage *psImage )
{
    const char *pachTRE;
    int        nTRESize;
    int        nBlockaLines;
    char       szTemp[128];


    pachTRE = NITFFindTRE( psImage->pachTRE, psImage->nTREBytes,
                           "BLOCKA", &nTRESize );

    if( pachTRE == NULL )
        return FALSE;

    if( nTRESize != 123 )
    {
        return FALSE;
    }


    if( pachTRE[34] == ' ' || pachTRE[55] == ' ' ||
        pachTRE[76] == ' ' || pachTRE[97] == ' ' )
    {
        return FALSE;
    }


    nBlockaLines = atoi(NITFGetField( szTemp, pachTRE, 7, 5 ));
    if( psImage->nRows != nBlockaLines )
    {
        return FALSE;
    }


    {
        double *pdfXYs = &(psImage->dfULX);

        NITFGetGCP ( pachTRE + 34, pdfXYs, 1 );
        NITFGetGCP ( pachTRE + 55, pdfXYs, 2 );
        NITFGetGCP ( pachTRE + 76, pdfXYs, 3 );
        NITFGetGCP ( pachTRE + 97, pdfXYs, 0 );

        psImage->bIsBoxCenterOfPixel = TRUE;
    }


    psImage->chICORDS = 'D';

    return TRUE;
}
