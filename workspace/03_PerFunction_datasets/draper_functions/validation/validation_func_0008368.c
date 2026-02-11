qiodevice_seek(jas_stream_obj_t *obj, long offset, int origin)
{
        QIODevice *io = (QIODevice*) obj;
        long newpos;

        switch (origin) {
        case SEEK_SET:
                newpos = offset;
                break;
        case SEEK_END:
                newpos = io->size() - offset;
                break;
        case SEEK_CUR:
                newpos = io->pos() + offset;
                break;
        default:
                return -1;
        }
        if (newpos < 0) {
                return -1;
        }
        if ( io->seek(newpos) )
            return newpos;
        else
            return -1;
}
