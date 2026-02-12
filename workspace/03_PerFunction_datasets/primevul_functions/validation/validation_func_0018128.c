static void encode_create_session(struct xdr_stream *xdr,
				  const struct nfs41_create_session_args *args,
				  struct compound_hdr *hdr)
{
	__be32 *p;
	struct nfs_client *clp = args->client;
	struct rpc_clnt *clnt = clp->cl_rpcclient;
	struct nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
	u32 max_resp_sz_cached;


	max_resp_sz_cached = (NFS4_dec_open_sz + RPC_REPHDRSIZE + 2)
				* XDR_UNIT + RPC_MAX_AUTH_SIZE;

	encode_op_hdr(xdr, OP_CREATE_SESSION, decode_create_session_maxsz, hdr);
	p = reserve_space(xdr, 16 + 2*28 + 20 + clnt->cl_nodelen + 12);
	p = xdr_encode_hyper(p, args->clientid);
	*p++ = cpu_to_be32(args->seqid);
	*p++ = cpu_to_be32(args->flags);


	*p++ = cpu_to_be32(0);
	*p++ = cpu_to_be32(args->fc_attrs.max_rqst_sz);
	*p++ = cpu_to_be32(args->fc_attrs.max_resp_sz);
	*p++ = cpu_to_be32(max_resp_sz_cached);
	*p++ = cpu_to_be32(args->fc_attrs.max_ops);
	*p++ = cpu_to_be32(args->fc_attrs.max_reqs);
	*p++ = cpu_to_be32(0);


	*p++ = cpu_to_be32(0);
	*p++ = cpu_to_be32(args->bc_attrs.max_rqst_sz);
	*p++ = cpu_to_be32(args->bc_attrs.max_resp_sz);
	*p++ = cpu_to_be32(args->bc_attrs.max_resp_sz_cached);
	*p++ = cpu_to_be32(args->bc_attrs.max_ops);
	*p++ = cpu_to_be32(args->bc_attrs.max_reqs);
	*p++ = cpu_to_be32(0);

	*p++ = cpu_to_be32(args->cb_program);
	*p++ = cpu_to_be32(1);
	*p++ = cpu_to_be32(RPC_AUTH_UNIX);


	*p++ = cpu_to_be32(ktime_to_ns(nn->boot_time));
	p = xdr_encode_array(p, clnt->cl_nodename, clnt->cl_nodelen);
	*p++ = cpu_to_be32(0);
	*p++ = cpu_to_be32(0);
	*p = cpu_to_be32(0);
}
