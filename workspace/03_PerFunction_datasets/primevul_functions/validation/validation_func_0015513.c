HttpStateData::truncateVirginBody()
{
    assert(flags.headers_parsed);

    HttpReply *vrep = virginReply();
    int64_t clen = -1;
    if (!vrep->expectingBody(request->method, clen) || clen < 0)
        return;

    if (payloadSeen - payloadTruncated <= clen)
        return;

    if (const int64_t extras = payloadSeen - payloadTruncated - clen) {

        debugs(11, 5, "payloadSeen=" << payloadSeen <<
               " clen=" << clen << '/' << vrep->content_length <<
               " trucated=" << payloadTruncated << '+' << extras);

        inBuf.chop(0, inBuf.length() - extras);
        payloadTruncated += extras;
    }
}
