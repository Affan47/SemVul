static __net_exit void ppp_exit_net(struct net *net)
{
	struct ppp_net *pn;

	pn = net_generic(net, ppp_net_id);
	idr_destroy(&pn->units_idr);


	net_assign_generic(net, ppp_net_id, NULL);
	kfree(pn);
}
