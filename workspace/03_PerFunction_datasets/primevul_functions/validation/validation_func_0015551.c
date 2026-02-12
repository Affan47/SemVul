HttpStateData::maybeMakeSpaceAvailable(bool doGrow)
{

    const int limitBuffer = (flags.headers_parsed ? Config.readAheadGap : Config.maxReplyHeaderSize);

    if (limitBuffer < 0 || inBuf.length() >= (SBuf::size_type)limitBuffer) {

        debugs(11, 7, "will not read up to " << limitBuffer << ". buffer has (" << inBuf.length() << "/" << inBuf.spaceSize() << ") from " << serverConnection);
        debugs(11, DBG_DATA, "buffer has {" << inBuf << "}");

        processReply();
        return false;
    }


    const size_t read_size = calcBufferSpaceToReserve(inBuf.spaceSize(), (limitBuffer - inBuf.length()));

    if (!read_size) {
        debugs(11, 7, "will not read up to " << read_size << " into buffer (" << inBuf.length() << "/" << inBuf.spaceSize() << ") from " << serverConnection);
        return false;
    }


    if (doGrow)
        return (read_size >= 2);


    inBuf.reserveSpace(read_size);
    debugs(11, 8, (!flags.do_next_read ? "will not" : "may") <<
           " read up to " << read_size << " bytes info buf(" << inBuf.length() << "/" << inBuf.spaceSize() <<
           ") from " << serverConnection);

    return (inBuf.spaceSize() >= 2);
}
