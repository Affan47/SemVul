close()
{
    p->zipError = UNZ_OK;
    switch(p->mode)
    {
    case mdNotOpen:
        qWarning("QuaZip::close(): ZIP is not open");
        return;
    case mdUnzip:
        p->zipError = unzClose(p->unzFile_f);
        break;
    case mdCreate:
    case mdAppend:
    case mdAdd:
        p->zipError = zipClose(p->zipFile_f,
                               p->comment.isNull() ? NULL
                               : p->commentCodec->fromUnicode(p->comment).constData());
        break;
    default:
        qWarning("QuaZip::close(): unknown mode: %d", (int)p->mode);
        return;
    }

    if(!p->zipName.isEmpty())
    {
        delete p->ioDevice;
        p->ioDevice = NULL;
    }
    if(p->zipError == UNZ_OK)
    {
        p->mode = mdNotOpen;
    }
}
