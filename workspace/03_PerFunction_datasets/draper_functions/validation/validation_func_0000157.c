transport_free_session(struct se_session *se_sess)
{
	struct se_node_acl *se_nacl = se_sess->se_node_acl;


	if (se_nacl) {
		struct se_portal_group *se_tpg = se_nacl->se_tpg;
		const struct target_core_fabric_ops *se_tfo = se_tpg->se_tpg_tfo;
		unsigned long flags;

		se_sess->se_node_acl = NULL;


		mutex_lock(&se_tpg->acl_node_mutex);
		if (se_nacl->dynamic_node_acl &&
		    !se_tfo->tpg_check_demo_mode_cache(se_tpg)) {
			spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
			if (list_empty(&se_nacl->acl_sess_list))
				se_nacl->dynamic_stop = true;
			spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);

			if (se_nacl->dynamic_stop)
				list_del_init(&se_nacl->acl_list);
		}
		mutex_unlock(&se_tpg->acl_node_mutex);

		if (se_nacl->dynamic_stop)
			target_put_nacl(se_nacl);

		target_put_nacl(se_nacl);
	}
	if (se_sess->sess_cmd_map) {
		percpu_ida_destroy(&se_sess->sess_tag_pool);
		kvfree(se_sess->sess_cmd_map);
	}
	kmem_cache_free(se_sess_cache, se_sess);
}
