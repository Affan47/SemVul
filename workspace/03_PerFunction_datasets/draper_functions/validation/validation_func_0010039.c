SetDirectory( toff_t nNewOffset )

{
    Crystalize();

    FlushBlockBuf();

    if( nNewOffset == 0 )
        nNewOffset = nDirOffset;

    if( TIFFCurrentDirOffset(hTIFF) == nNewOffset )
    {
        CPLAssert( *ppoActiveDSRef == this || *ppoActiveDSRef == NULL );
        *ppoActiveDSRef = this;
        return TRUE;
    }

    if( GetAccess() == GA_Update )
    {
        if( *ppoActiveDSRef != NULL )
            (*ppoActiveDSRef)->FlushDirectory();
    }

    if( nNewOffset == 0)
        return TRUE;

    (*ppoActiveDSRef) = this;

    int nSetDirResult = TIFFSetSubDirectory( hTIFF, nNewOffset );
    if (!nSetDirResult)
        return nSetDirResult;


    if( !TIFFGetField( hTIFF, TIFFTAG_COMPRESSION, &(nCompression) ) )
        nCompression = COMPRESSION_NONE;

    if( !TIFFGetField( hTIFF, TIFFTAG_PHOTOMETRIC, &(nPhotometric) ) )
        nPhotometric = PHOTOMETRIC_MINISBLACK;

    if( nCompression == COMPRESSION_JPEG
        && nPhotometric == PHOTOMETRIC_YCBCR
        && CSLTestBoolean( CPLGetConfigOption("CONVERT_YCBCR_TO_RGB",
                                              "YES") ) )
    {
        int nColorMode;

        TIFFGetField( hTIFF, TIFFTAG_JPEGCOLORMODE, &nColorMode );
        if( nColorMode != JPEGCOLORMODE_RGB )
            TIFFSetField(hTIFF, TIFFTAG_JPEGCOLORMODE, JPEGCOLORMODE_RGB);
    }


    if( GetAccess() == GA_Update )
    {

        if(nJpegQuality > 0 && nCompression == COMPRESSION_JPEG)
        {
            CPLDebug( "GTiff", "Propgate JPEG_QUALITY(%d) in SetDirectory()",
                      nJpegQuality );
            TIFFSetField(hTIFF, TIFFTAG_JPEGQUALITY, nJpegQuality);
        }
        if(nZLevel > 0 && nCompression == COMPRESSION_ADOBE_DEFLATE)
            TIFFSetField(hTIFF, TIFFTAG_ZIPQUALITY, nZLevel);
        if(nLZMAPreset > 0 && nCompression == COMPRESSION_LZMA)
            TIFFSetField(hTIFF, TIFFTAG_LZMAPRESET, nLZMAPreset);
    }

    return nSetDirResult;
}
