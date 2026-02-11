ncp_symlink_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int error, length, len;
	char *link, *rawlink;
	char *buf = kmap(page);

	error = -ENOMEM;
	rawlink = kmalloc(NCP_MAX_SYMLINK_SIZE, GFP_KERNEL);
	if (!rawlink)
		goto fail;

	if (ncp_make_open(inode,O_RDONLY))
		goto failEIO;

	error=ncp_read_kernel(NCP_SERVER(inode),NCP_FINFO(inode)->file_handle,
                         0,NCP_MAX_SYMLINK_SIZE,rawlink,&length);

	ncp_inode_close(inode);

	ncp_make_closed(inode);
	if (error)
		goto failEIO;

	if (NCP_FINFO(inode)->flags & NCPI_KLUDGE_SYMLINK) {
		if (length<NCP_MIN_SYMLINK_SIZE ||
		    ((__le32 *)rawlink)[0]!=NCP_SYMLINK_MAGIC0 ||
		    ((__le32 *)rawlink)[1]!=NCP_SYMLINK_MAGIC1)
		    	goto failEIO;
		link = rawlink + 8;
		length -= 8;
	} else {
		link = rawlink;
	}

	len = NCP_MAX_SYMLINK_SIZE;
	error = ncp_vol2io(NCP_SERVER(inode), buf, &len, link, length, 0);
	kfree(rawlink);
	if (error)
		goto fail;
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;

failEIO:
	error = -EIO;
	kfree(rawlink);
fail:
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return error;
}
