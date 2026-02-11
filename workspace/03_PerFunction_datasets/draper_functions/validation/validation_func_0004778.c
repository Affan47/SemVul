rename_err(void)
{
    if (errno == EISDIR)
	return NFS3ERR_ISDIR;
    else if (errno == EXDEV)
	return NFS3ERR_XDEV;
    else if (errno == EEXIST)
	return NFS3ERR_EXIST;
    else if (errno == ENOTEMPTY)
	return NFS3ERR_NOTEMPTY;
    else if (errno == EINVAL)
	return NFS3ERR_INVAL;
    else if (errno == ENOTDIR)
	return NFS3ERR_NOTDIR;
    else if (errno == EACCES || errno == EPERM)
	return NFS3ERR_ACCES;
    else if (errno == ENOENT)
	return NFS3ERR_NOENT;
    else if (errno == ELOOP || errno == ENAMETOOLONG)
	return NFS3ERR_STALE;
    else if (errno == EROFS)
	return NFS3ERR_ROFS;
    else if (errno == ENOSPC)
	return NFS3ERR_NOSPC;
#ifdef EDQUOT
    else if (errno == EDQUOT)
	return NFS3ERR_DQUOT;
#endif
    else
	return NFS3ERR_IO;
}
