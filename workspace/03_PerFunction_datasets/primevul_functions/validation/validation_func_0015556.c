HttpStateData::persistentConnStatus() const
{
    debugs(11, 3, HERE << serverConnection << " eof=" << eof);
    if (eof)
        return COMPLETE_NONPERSISTENT_MSG;


    if (!Comm::IsConnOpen(serverConnection))
        return COMPLETE_NONPERSISTENT_MSG;


    if (lastChunk && flags.chunked)
        return statusIfComplete();

    const HttpReply *vrep = virginReply();
    debugs(11, 5, "persistentConnStatus: content_length=" << vrep->content_length);

    const int64_t clen = vrep->bodySize(request->method);

    debugs(11, 5, "persistentConnStatus: clen=" << clen);


    if (clen < 0)
        return INCOMPLETE_MSG;


    if (clen > 0) {
        debugs(11,5, "payloadSeen=" << payloadSeen << " content_length=" << vrep->content_length);

        if (payloadSeen < vrep->content_length)
            return INCOMPLETE_MSG;

        if (payloadTruncated > 0)
            return COMPLETE_NONPERSISTENT_MSG;
    }


    return statusIfComplete();
}
