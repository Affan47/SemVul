static inline u32 nfsd4_offload_status_rsize(struct svc_rqst *rqstp,
					     struct nfsd4_op *op)
{
	return (op_encode_hdr_size +
		2  +
		1 ) * sizeof(__be32);
}
