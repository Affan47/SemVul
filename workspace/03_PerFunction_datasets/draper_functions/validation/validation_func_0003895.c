CORD_from_file_lazy(FILE * f)
{
    register long len;

    if (fseek(f, 0l, SEEK_END) != 0) {
        ABORT("Bad fd argument - fseek failed");
    }
    if ((len = ftell(f)) < 0) {
        ABORT("Bad fd argument - ftell failed");
    }
    rewind(f);
    return(CORD_from_file_lazy_inner(f, (size_t)len));
}
