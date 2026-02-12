static __be32 nfsd4_do_copy(struct nfsd4_copy *copy, bool sync)
{
	__be32 status;
	ssize_t bytes;

	bytes = _nfsd_copy_file_range(copy);


	if (bytes < 0 && !copy->cp_res.wr_bytes_written)
		status = nfserrno(bytes);
	else {
		nfsd4_init_copy_res(copy, sync);
		status = nfs_ok;
	}

	fput(copy->file_src);
	fput(copy->file_dst);
	return status;
}
