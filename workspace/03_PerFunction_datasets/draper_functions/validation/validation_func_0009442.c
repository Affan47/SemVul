putFileContentsIntoElement(DcmElement *elem, const char *filename)
{
    OFCondition ec = EC_Normal;
#ifdef EXPERIMENTAL_READ_FROM_FILE

    DcmInputFileStream fileStream(filename);
    ec = fileStream.status();
    if (ec.good())
    {

        const size_t fileLen = OFStandard::getFileSize(filename);

        ec = elem->createValueFromTempFile(fileStream.newFactory(), fileLen, EBO_LittleEndian);
        if (ec.bad())
            OFLOG_ERROR(dump2dcmLogger, "cannot process binary data file: " << filename);
    } else {
        OFLOG_ERROR(dump2dcmLogger, "cannot open binary data file: " << filename);
        ec = EC_InvalidTag;
    }
#else
    FILE *f = NULL;
    if ((f = fopen(filename, "rb")) == NULL)
    {
        OFLOG_ERROR(dump2dcmLogger, "cannot open binary data file: " << filename);
        return EC_InvalidTag;
    }

    const size_t len = OFStandard::getFileSize(filename);
    unsigned long buflen = len;
    if (buflen & 1)
        buflen++;

    Uint8 *buf = NULL;
    const DcmEVR evr = elem->getVR();

    if (evr == EVR_OB || evr == EVR_pixelItem)
        ec = elem->createUint8Array(buflen, buf);
    else if (evr == EVR_OW)
    {
        Uint16 *buf16 = NULL;
        ec = elem->createUint16Array(buflen / 2, buf16);
        buf = OFreinterpret_cast(Uint8 *, buf16);
    } else
        ec = EC_IllegalCall;
    if (ec.good())
    {

        if (fread(buf, 1, OFstatic_cast(size_t, len), f) != len)
        {
            char errBuf[256];
            OFLOG_ERROR(dump2dcmLogger, "error reading binary data file: " << filename
                << ": " << OFStandard::strerror(errno, errBuf, sizeof(errBuf)));
            ec = EC_CorruptedData;
        }
        else if (evr == EVR_OW)
        {

            swapIfNecessary(gLocalByteOrder, opt_fileContentsByteOrdering, buf, buflen, sizeof(Uint16));
        }
    }
    else if (ec == EC_MemoryExhausted)
        OFLOG_ERROR(dump2dcmLogger, "out of memory reading binary data file: " << filename);
    else
        OFLOG_ERROR(dump2dcmLogger, "illegal call processing binary data file: " << filename);

    fclose(f);
#endif
    return ec;
}
