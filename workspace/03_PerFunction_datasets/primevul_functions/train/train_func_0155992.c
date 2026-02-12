getChunkOffsetTableSize(const Header& header)
{


    if(header.hasType()  && !isSupportedType(header.type()))
    {
        if(header.hasChunkCount())
        {
           return header.chunkCount();
        }
        else
        {
           throw IEX_NAMESPACE::ArgExc ("unsupported header type to "
           "get chunk offset table size");
        }
    }


    if (isTiled(header.type()) == false)
        return getScanlineChunkOffsetTableSize(header);
    else
        return getTiledChunkOffsetTableSize(header);

}
