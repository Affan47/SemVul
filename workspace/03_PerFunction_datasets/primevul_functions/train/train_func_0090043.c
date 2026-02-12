RecordABigRequest(RecordContextPtr pContext, ClientPtr client, xReq * stuff)
{
    CARD32 bigLength;
    int bytesLeft;


    bytesLeft = client->req_len << 2;
    RecordAProtocolElement(pContext, client, XRecordFromClient,
                           (void *) stuff, SIZEOF(xReq), 0, bytesLeft);


    bigLength = client->req_len + bytes_to_int32(sizeof(bigLength));
    if (client->swapped)
        swapl(&bigLength);
    RecordAProtocolElement(pContext, client, XRecordFromClient,
                           (void *) &bigLength, sizeof(bigLength), 0,
                            -1);
    bytesLeft -= sizeof(bigLength);


    RecordAProtocolElement(pContext, client, XRecordFromClient,
                           (void *) (stuff + 1), bytesLeft, 0,
                            -1);
}
