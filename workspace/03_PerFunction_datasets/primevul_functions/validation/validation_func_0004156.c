IsoPresentation_createCpaMessage(IsoPresentation* self, BufferChain writeBuffer, BufferChain payload)
{
    int contentLength = 0;


    contentLength += 5;

    int normalModeLength = 0;

    normalModeLength += 6;

    normalModeLength += 20;

    normalModeLength += encodeUserData(NULL, 0, payload, false, self->acseContextId);

    contentLength += normalModeLength;

    contentLength += BerEncoder_determineLengthSize(normalModeLength) + 1;

    uint8_t* buffer = writeBuffer->buffer;
    int bufPos = 0;

    bufPos = BerEncoder_encodeTL(0x31, contentLength, buffer, bufPos);


    bufPos = BerEncoder_encodeTL(0xa0, 3, buffer, bufPos);
    bufPos = BerEncoder_encodeTL(0x80, 1, buffer, bufPos);
    buffer[bufPos++] = 1;


    bufPos = BerEncoder_encodeTL(0xa2, normalModeLength, buffer, bufPos);


    bufPos = BerEncoder_encodeTL(0x83, 4, buffer, bufPos);
    memcpy(buffer + bufPos, calledPresentationSelector, 4);
    bufPos += 4;


    bufPos = BerEncoder_encodeTL(0xa5, 18, buffer, bufPos);
    bufPos = encodeAcceptBer(buffer, bufPos);
    bufPos = encodeAcceptBer(buffer, bufPos);


    bufPos = encodeUserData(buffer, bufPos, payload, true, self->acseContextId);

    writeBuffer->partLength = bufPos;
    writeBuffer->length = bufPos + payload->length;
    writeBuffer->nextPart = payload;
}
