mysql_ds_fixup(void *data, struct ast_channel *oldchan, struct ast_channel *newchan)
{

	struct ast_MYSQL_id *i;
	if (AST_LIST_LOCK(&_mysql_ids_head)) {
		ast_log(LOG_WARNING, "Unable to lock identifiers list\n");
	} else {
		AST_LIST_TRAVERSE_SAFE_BEGIN(&_mysql_ids_head, i, entries) {
			if (i->owner == data) {
				AST_LIST_REMOVE_CURRENT(entries);
				if (i->identifier_type == AST_MYSQL_ID_CONNID) {

					mysql_close(i->data);
				} else if (i->identifier_type == AST_MYSQL_ID_RESID) {

					mysql_free_result(i->data);
				}
				ast_free(i);
			}
		}
		AST_LIST_TRAVERSE_SAFE_END
		AST_LIST_UNLOCK(&_mysql_ids_head);
	}
}
