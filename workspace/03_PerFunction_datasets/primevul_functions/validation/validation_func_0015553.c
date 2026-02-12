HttpStateData::getMoreRequestBody(MemBuf &buf)
{

    if (!flags.chunked_request)
        return Client::getMoreRequestBody(buf);

    MemBuf raw;

    Must(requestBodySource != NULL);
    if (!requestBodySource->getMoreData(raw))
        return false;


    const mb_size_t rawDataSize = raw.contentSize();

    buf.init(16 + 2 + rawDataSize + 2 + 5, raw.max_capacity);

    buf.appendf("%x\r\n", static_cast<unsigned int>(rawDataSize));
    buf.append(raw.content(), rawDataSize);
    buf.append("\r\n", 2);

    Must(rawDataSize > 0);


    if (receivedWholeRequestBody) {
        Must(!flags.sentLastChunk);
        flags.sentLastChunk = true;
        buf.append("0\r\n\r\n", 5);
    }

    return true;
}
