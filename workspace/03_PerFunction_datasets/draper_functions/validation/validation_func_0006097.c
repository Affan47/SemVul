nfsd_export_shutdown(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprintk("nfsd: shutting down export module (net: %p).\n", net);

	cache_unregister_net(nn->svc_expkey_cache, net);
	cache_unregister_net(nn->svc_export_cache, net);
	cache_destroy_net(nn->svc_expkey_cache, net);
	cache_destroy_net(nn->svc_export_cache, net);
	svcauth_unix_purge(net);

	dprintk("nfsd: export shutdown complete (net: %p).\n", net);
}
