static void tipc_node_calculate_timer(struct tipc_node *n, struct tipc_link *l)
{
	unsigned long tol = tipc_link_tolerance(l);
	unsigned long intv = ((tol / 4) > 500) ? 500 : tol / 4;


	if (intv < n->keepalive_intv)
		n->keepalive_intv = intv;


	tipc_link_set_abort_limit(l, tol / n->keepalive_intv);
}
