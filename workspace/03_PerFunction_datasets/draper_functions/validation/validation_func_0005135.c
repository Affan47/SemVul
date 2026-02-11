_2BUSWriteData(reader* globalData, uchar socket, ushort address,
                          uchar* data, int len, uchar* outBuffer, int *outBufLen) {
    int retVal = ASE_OK, counter = 0, writeLen = len;
    ushort maxAddress = 0;
    uchar cmdCode = 0, thisWrite;
    uchar mode = globalData->cards[(int)socket].memCard.memType;

    switch (mode) {
        case MEM_CARD_MAIN_MEM_MODE:
            if (address > _2BUS_MAX_ADDRESS)
                retVal = MEM_CARD_ILLEGAL_ADDRESS;
            else {
                maxAddress = _2BUS_MAX_ADDRESS;
                cmdCode = _2BUS_UPDATE_DATA;
            }
            break;
        case MEM_CARD_PROT_MEM_MODE:
            if (address > _2BUS_MAX_PROTECTED_ADDRESS)
                retVal = MEM_CARD_ILLEGAL_ADDRESS;
            else {
                maxAddress = _2BUS_MAX_PROTECTED_ADDRESS;
                cmdCode = _2BUS_PROTECT_DATA_COND;
            }
            break;
        default:
            retVal = MEM_CARD_BAD_MODE;
            break;
    }

    if (retVal == ASE_OK) {

        if (len > (maxAddress - address + 1)) {
            retVal = MEM_CARD_WRONG_LENGTH;
        }
        else {
            while (counter < len && retVal == ASE_OK) {
                thisWrite = (writeLen > MEM_CARD_WRITE_CHUNK_SIZE ? MEM_CARD_WRITE_CHUNK_SIZE : writeLen);
                retVal = _2BUSExecOutCommand(globalData, socket, cmdCode,
                                             address + counter, data + counter, thisWrite,
                                             outBuffer, outBufLen);
                counter += thisWrite;
                writeLen -= thisWrite;
            }
        }
    }

    if (retVal < 0)
        retVal = MEM_CARD_WRITE_FAILED;

    AddSW1SW2(retVal, outBuffer, outBufLen, 0);

    return ASE_OK;
}
