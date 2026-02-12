encode_layoutcommit(struct xdr_stream *xdr,
		    struct inode *inode,
		    const struct nfs4_layoutcommit_args *args,
		    struct compound_hdr *hdr)
{
	__be32 *p;

	dprintk("%s: lbw: %llu type: %d\n", __func__, args->lastbytewritten,
		NFS_SERVER(args->inode)->pnfs_curr_ld->id);

	encode_op_hdr(xdr, OP_LAYOUTCOMMIT, decode_layoutcommit_maxsz, hdr);
	p = reserve_space(xdr, 20);

	p = xdr_encode_hyper(p, 0);
	p = xdr_encode_hyper(p, args->lastbytewritten + 1);
	*p = cpu_to_be32(0);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 20);
	*p++ = cpu_to_be32(1);
	p = xdr_encode_hyper(p, args->lastbytewritten);
	*p++ = cpu_to_be32(0);
	*p++ = cpu_to_be32(NFS_SERVER(args->inode)->pnfs_curr_ld->id);

	if (NFS_SERVER(inode)->pnfs_curr_ld->encode_layoutcommit)
		NFS_SERVER(inode)->pnfs_curr_ld->encode_layoutcommit(
			NFS_I(inode)->layout, xdr, args);
	else
		encode_uint32(xdr, 0);

	return 0;
}
