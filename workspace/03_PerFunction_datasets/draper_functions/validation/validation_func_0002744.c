hpaioProgramOptions( hpaioScanner_t hpaio )
{
    int bytes_wrote;

    hpaio->effectiveScanMode = hpaio->currentScanMode;
    hpaio->effectiveResolution = hpaio->currentResolution;


        switch( hpaio->currentScanMode )
        {
            case SCAN_MODE_LINEART:
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_OUTPUT_DATA_TYPE,
                                SCL_DATA_TYPE_LINEART );
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_DATA_WIDTH,
                                SCL_DATA_WIDTH_LINEART );
                break;

            case SCAN_MODE_GRAYSCALE:
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_OUTPUT_DATA_TYPE,
                                SCL_DATA_TYPE_GRAYSCALE );
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_DATA_WIDTH,
                                SCL_DATA_WIDTH_GRAYSCALE );
                break;

            case SCAN_MODE_COLOR:
            default:
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_OUTPUT_DATA_TYPE,
                                SCL_DATA_TYPE_COLOR );
                SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                                SCL_CMD_SET_DATA_WIDTH,
                                SCL_DATA_WIDTH_COLOR );
                break;
        }


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_MFPDTF,
                        hpaio->mfpdtf ? SCL_MFPDTF_ON : SCL_MFPDTF_OFF );


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_COMPRESSION,
                        ( hpaio->currentCompression ==
                          COMPRESSION_JPEG ? SCL_COMPRESSION_JPEG : SCL_COMPRESSION_NONE ) );


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_JPEG_COMPRESSION_FACTOR,
                        hpaio->currentJpegCompressionFactor );


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_X_RESOLUTION,
                        hpaio->currentResolution );

        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_Y_RESOLUTION,
                        hpaio->currentResolution );


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_X_POSITION,
                        MILLIMETERS_TO_DECIPIXELS( hpaio->effectiveTlx ) );

        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_Y_POSITION,
                        MILLIMETERS_TO_DECIPIXELS( hpaio->effectiveTly ) );

        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_X_EXTENT,
                        MILLIMETERS_TO_DECIPIXELS( hpaio->effectiveBrx -
                                                   hpaio->effectiveTlx ) );

        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_Y_EXTENT,
                        MILLIMETERS_TO_DECIPIXELS( hpaio->effectiveBry -
                                                   hpaio->effectiveTly ) );

        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_CONTRAST,
                        hpaio->currentContrast );


        SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                        SCL_CMD_SET_BRIGHTNESS,
                        hpaio->currentBrightness );


        if( hpaio->scl.compat & ( SCL_COMPAT_1150 | SCL_COMPAT_1170 ) )
        {
            SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                            SCL_CMD_SET_DOWNLOAD_TYPE,
                            SCL_DOWNLOAD_TYPE_COLORMAP );

            SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                            SCL_CMD_DOWNLOAD_BINARY_DATA,
                            sizeof( hp11xxSeriesColorMap ) );

            hpmud_write_channel(hpaio->deviceid, hpaio->scan_channelid, hp11xxSeriesColorMap, sizeof(hp11xxSeriesColorMap),
                        EXCEPTION_TIMEOUT, &bytes_wrote);
        }


        if( hpaio->scl.compat & SCL_COMPAT_R_SERIES &&
            hpaio->currentScanMode == SCAN_MODE_LINEART )
        {
            SclSendCommand( hpaio->deviceid, hpaio->scan_channelid,
                            SCL_CMD_SET_CCD_RESOLUTION, 600 );
        }

    return SANE_STATUS_GOOD;
}
