s_file_read_close(stream * s)
{
    FILE *file = s->file;

    if (file != 0) {
        s->file = 0;
        return (fclose(file) ? ERRC : 0);
    }
    return 0;
}
