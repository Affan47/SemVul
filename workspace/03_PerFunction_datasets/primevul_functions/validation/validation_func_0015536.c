HttpStateData::writeReplyBody()
{
    truncateVirginBody();
    const char *data = inBuf.rawContent();
    int len = inBuf.length();
    addVirginReplyBody(data, len);
    inBuf.consume(len);
}
