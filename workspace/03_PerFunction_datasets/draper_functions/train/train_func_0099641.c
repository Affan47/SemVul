full_write(void *data, size_t size)
{
    if (fwrite(data, size, 1, idxfile) != 1) {
	dico_log(L_ERR, errno, _("write error"));
	exit(EX_UNAVAILABLE);
    }
}
