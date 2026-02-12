encodeUserData(uint8_t* buffer, int bufPos,
        BufferChain payload, bool encode, uint8_t contextId)
{
    int payloadLength = payload->length;

    int encodedDataSetLength = 3;


    encodedDataSetLength += payloadLength + 1;
    encodedDataSetLength += BerEncoder_determineLengthSize(payloadLength);

    int fullyEncodedDataLength = encodedDataSetLength;

    fullyEncodedDataLength += BerEncoder_determineLengthSize(encodedDataSetLength) + 1;

    if (encode) {

        bufPos = BerEncoder_encodeTL(0x61, fullyEncodedDataLength, buffer, bufPos);
        bufPos = BerEncoder_encodeTL(0x30, encodedDataSetLength, buffer, bufPos);


        bufPos = BerEncoder_encodeTL(0x02, 1, buffer, bufPos);
        buffer[bufPos++] = contextId;


        bufPos = BerEncoder_encodeTL(0xa0, payloadLength, buffer, bufPos);

        return bufPos;
    }
    else {
        int encodedUserDataLength = fullyEncodedDataLength + 1;
        encodedUserDataLength += BerEncoder_determineLengthSize(fullyEncodedDataLength);

        return encodedUserDataLength;
    }
}
