readPDUBody(PRIVATE_ASSOCIATIONKEY ** association,
            DUL_BLOCKOPTIONS block, int timeout,
            unsigned char *buffer, unsigned long maxLength,
            unsigned char *pduType, unsigned char *pduReserved,
            unsigned long *pduLength)
{
    OFCondition cond = EC_Normal;


    cond = readPDUBodyTCP(association, block, timeout, buffer, maxLength,
                          pduType, pduReserved, pduLength);


    (*association)->inputPDU = NO_PDU;


    return cond;
}
