freadFile(Expr_t * ex, int fd)
{
    Sfio_t *sp;

    if (fd < 0 || fd >= elementsof(ex->file)
	|| !((sp = ex->file[fd]))) {
	exerror("freadG: %d: invalid descriptor", fd);
	return 0;
    }
    return readG(sp);
}
