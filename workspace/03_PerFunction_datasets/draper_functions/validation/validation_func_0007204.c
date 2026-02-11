mf_read(mfp, hp)
    memfile_T	*mfp;
    bhdr_T	*hp;
{
    off_t	offset;
    unsigned	page_size;
    unsigned	size;

    if (mfp->mf_fd < 0)
	return FAIL;

    page_size = mfp->mf_page_size;
    offset = (off_t)page_size * hp->bh_bnum;
    size = page_size * hp->bh_page_count;
    if (lseek(mfp->mf_fd, offset, SEEK_SET) != offset)
    {
	PERROR(_("E294: Seek error in swap file read"));
	return FAIL;
    }
    if ((unsigned)vim_read(mfp->mf_fd, hp->bh_data, size) != size)
    {
	PERROR(_("E295: Read error in swap file"));
	return FAIL;
    }
    return OK;
}
