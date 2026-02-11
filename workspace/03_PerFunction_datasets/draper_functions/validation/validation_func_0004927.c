ay_chat_window_fellows_remove(chat_window *cw, ConversationFellow *fellow)
{
	GtkTreeIter del_iter;

	if (!gtk_tree_model_get_iter_first(GTK_TREE_MODEL(cw->fellows_model), &del_iter)) {
		eb_debug(DBG_CORE, "Nothing in the list yet??: %s\n", fellow->alias);
		return;
	}

	do {
		char *name = NULL;

		gtk_tree_model_get(GTK_TREE_MODEL(cw->fellows_model),
			&del_iter, 0, &name, -1);

		if (!strcmp(name, fellow->alias)) {
			gtk_list_store_remove(cw->fellows_model,
				&del_iter);
			return;
		}
	} while (gtk_tree_model_iter_next(GTK_TREE_MODEL(cw->
				fellows_model), &del_iter));
}
