floppy_wait(struct remote *rem, void *data, avoff_t end)
{
    int res;
    struct floppylocalfile *lf = (struct floppylocalfile *) data;


    do {
        struct stat stbuf;

        res = av_program_log_output(lf->pr);
        if(res <= 0)
            return res;

        res = stat(lf->tmpfile, &stbuf);
        if(res == 0)
            lf->currsize = stbuf.st_size;

        if(lf->currsize < end)
            av_sleep(250);

    } while(lf->currsize < end);

    return 1;
}
