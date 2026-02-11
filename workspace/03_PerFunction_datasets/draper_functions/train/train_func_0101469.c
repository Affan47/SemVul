db_quota_set_common(struct quota *q, const char *name, int is_group)
{
	struct db_quota_arg *arg = db_quota_arg_alloc(q, name, is_group);

	if (arg == NULL) {
		gflog_debug(GFARM_MSG_1002048,
			"db_quota_arg_alloc() failed");
		return (GFARM_ERR_NO_MEMORY);
	}

	if (q->on_db)
		return (dbq_enter(&dbq, (dbq_entry_func_t)ops->quota_modify,
				  arg));
	else
		return (dbq_enter(&dbq, (dbq_entry_func_t)ops->quota_add,
				  arg));
}
