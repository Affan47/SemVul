static void nfs4_setup_readdir(u64 cookie, __be32 *verifier, struct dentry *dentry,
		struct nfs4_readdir_arg *readdir)
{
	unsigned int attrs = FATTR4_WORD0_FILEID | FATTR4_WORD0_TYPE;
	__be32 *start, *p;

	if (cookie > 2) {
		readdir->cookie = cookie;
		memcpy(&readdir->verifier, verifier, sizeof(readdir->verifier));
		return;
	}

	readdir->cookie = 0;
	memset(&readdir->verifier, 0, sizeof(readdir->verifier));
	if (cookie == 2)
		return;


	start = p = kmap_atomic(*readdir->pages);

	if (cookie == 0) {
		*p++ = xdr_one;
		*p++ = xdr_zero;
		*p++ = xdr_one;
		*p++ = xdr_one;
		memcpy(p, ".\0\0\0", 4);
		p++;
		*p++ = xdr_one;
		*p++ = htonl(attrs);
		*p++ = htonl(12);
		*p++ = htonl(NF4DIR);
		p = xdr_encode_hyper(p, NFS_FILEID(d_inode(dentry)));
	}

	*p++ = xdr_one;
	*p++ = xdr_zero;
	*p++ = xdr_two;
	*p++ = xdr_two;
	memcpy(p, "..\0\0", 4);
	p++;
	*p++ = xdr_one;
	*p++ = htonl(attrs);
	*p++ = htonl(12);
	*p++ = htonl(NF4DIR);
	p = xdr_encode_hyper(p, NFS_FILEID(d_inode(dentry->d_parent)));

	readdir->pgbase = (char *)p - (char *)start;
	readdir->count -= readdir->pgbase;
	kunmap_atomic(start);
}
