clusterip_config_entry_put(struct clusterip_config *c)
{
	local_bh_disable();
	if (atomic_dec_and_lock(&c->entries, &clusterip_lock)) {
		list_del_rcu(&c->list);
		spin_unlock(&clusterip_lock);
		local_bh_enable();

		dev_mc_del(c->dev, c->clustermac);
		dev_put(c->dev);


#ifdef CONFIG_PROC_FS
		remove_proc_entry(c->pde->name, c->pde->parent);
#endif
		return;
	}
	local_bh_enable();
}
