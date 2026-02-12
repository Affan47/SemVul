HttpStateData::doneSendingRequestBody()
{
    Client::doneSendingRequestBody();
    debugs(11,5, HERE << serverConnection);


    if (flags.chunked_request && finishingChunkedRequest())
        return;
    if (!flags.chunked_request && finishingBrokenPost())
        return;

    sendComplete();
}
