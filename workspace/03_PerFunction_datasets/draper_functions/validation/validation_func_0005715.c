target_show_dynamic_sessions(struct se_portal_group *se_tpg, char *page)
{
	struct se_session *se_sess;
	ssize_t len = 0;

	spin_lock_bh(&se_tpg->session_lock);
	list_for_each_entry(se_sess, &se_tpg->tpg_sess_list, sess_list) {
		if (!se_sess->se_node_acl)
			continue;
		if (!se_sess->se_node_acl->dynamic_node_acl)
			continue;
		if (strlen(se_sess->se_node_acl->initiatorname) + 1 + len > PAGE_SIZE)
			break;

		len += snprintf(page + len, PAGE_SIZE - len, "%s\n",
				se_sess->se_node_acl->initiatorname);
		len += 1;
	}
	spin_unlock_bh(&se_tpg->session_lock);

	return len;
}
