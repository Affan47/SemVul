void JBIG2Stream::reset()
{
    segments.resize(0);
    globalSegments.resize(0);


    if (globalsStream.isStream()) {
        curStr = globalsStream.getStream();
        curStr->reset();
        arithDecoder->setStream(curStr);
        huffDecoder->setStream(curStr);
        mmrDecoder->setStream(curStr);
        readSegments();
        curStr->close();

        std::swap(segments, globalSegments);
    }


    curStr = str;
    curStr->reset();
    arithDecoder->setStream(curStr);
    huffDecoder->setStream(curStr);
    mmrDecoder->setStream(curStr);
    readSegments();

    if (pageBitmap) {
        dataPtr = pageBitmap->getDataPtr();
        dataEnd = dataPtr + pageBitmap->getDataSize();
    } else {
        dataPtr = dataEnd = nullptr;
    }
}
