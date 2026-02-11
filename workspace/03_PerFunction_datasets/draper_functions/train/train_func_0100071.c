hseek(hFILE *fp, off_t offset, int whence)
{
    off_t pos;

    if (writebuffer_is_nonempty(fp)) {
        int ret = flush_buffer(fp);
        if (ret < 0) return ret;
    }

    pos = fp->backend->seek(fp, offset, whence);
    if (pos < 0) { fp->has_errno = errno; return pos; }


    fp->begin = fp->end = fp->buffer;
    fp->at_eof = 0;

    fp->offset = pos;
    return pos;
}
