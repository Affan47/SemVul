void ovs_dp_detach_port(struct vport *p)
{
	ASSERT_OVSL();


	hlist_del_rcu(&p->dp_hash_node);


	ovs_vport_del(p);
}
