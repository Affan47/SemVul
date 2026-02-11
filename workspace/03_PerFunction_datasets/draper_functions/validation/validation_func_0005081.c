vm_users_data_provider_get_helper(const struct ast_data_search *search,
    struct ast_data *data_root, struct ast_vm_user *user)
{
	struct ast_data *data_user, *data_zone;
	struct ast_data *data_state;
	struct vm_zone *zone = NULL;
	int urgentmsg = 0, newmsg = 0, oldmsg = 0;
	char ext_context[256] = "";

	data_user = ast_data_add_node(data_root, "user");
	if (!data_user) {
		return -1;
	}

	ast_data_add_structure(ast_vm_user, data_user, user);

	AST_LIST_LOCK(&zones);
	AST_LIST_TRAVERSE(&zones, zone, list) {
		if (!strcmp(zone->name, user->zonetag)) {
			break;
		}
	}
	AST_LIST_UNLOCK(&zones);


	data_state = ast_data_add_node(data_user, "state");
	if (!data_state) {
		return -1;
	}
	snprintf(ext_context, sizeof(ext_context), "%s@%s", user->mailbox, user->context);
	inboxcount2(ext_context, &urgentmsg, &newmsg, &oldmsg);
	ast_data_add_int(data_state, "urgentmsg", urgentmsg);
	ast_data_add_int(data_state, "newmsg", newmsg);
	ast_data_add_int(data_state, "oldmsg", oldmsg);

	if (zone) {
		data_zone = ast_data_add_node(data_user, "zone");
		ast_data_add_structure(vm_zone, data_zone, zone);
	}

	if (!ast_data_search_match(search, data_user)) {
		ast_data_remove_node(data_root, data_user);
	}

	return 0;
}
