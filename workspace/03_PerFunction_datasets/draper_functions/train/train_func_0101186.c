make_space(struct config_group *g, const char *name)
{
	struct dlm_space *sp = NULL;
	struct dlm_nodes *nds = NULL;
	void *gps = NULL;

	sp = kzalloc(sizeof(struct dlm_space), GFP_NOFS);
	gps = kcalloc(2, sizeof(struct config_group *), GFP_NOFS);
	nds = kzalloc(sizeof(struct dlm_nodes), GFP_NOFS);

	if (!sp || !gps || !nds)
		goto fail;

	config_group_init_type_name(&sp->group, name, &space_type);
	config_group_init_type_name(&nds->ns_group, "nodes", &nodes_type);

	sp->group.default_groups = gps;
	sp->group.default_groups[0] = &nds->ns_group;
	sp->group.default_groups[1] = NULL;

	INIT_LIST_HEAD(&sp->members);
	mutex_init(&sp->members_lock);
	sp->members_count = 0;
	return &sp->group;

 fail:
	kfree(sp);
	kfree(gps);
	kfree(nds);
	return ERR_PTR(-ENOMEM);
}
