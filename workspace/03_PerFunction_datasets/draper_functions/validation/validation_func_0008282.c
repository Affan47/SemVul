kb_update(void)
{
	GtkTreeModel *model = GTK_TREE_MODEL(store);
	GtkTreeIter child, parent;
	guint gid = 0;


	if (! gtk_tree_model_iter_children(model, &parent, NULL))
		return;


	while (TRUE)
	{

		if (! gtk_tree_model_iter_children(model, &child, &parent))
			return;


		while (TRUE)
		{
			guint kid;
			gchar *str;
			guint key;
			GdkModifierType mods;
			GeanyKeyBinding *kb;

			gtk_tree_model_get(model, &child, KB_TREE_INDEX, &kid, KB_TREE_SHORTCUT, &str, -1);
			gtk_accelerator_parse(str, &key, &mods);
			g_free(str);
			kb = kb_index(gid, kid);
			if (kb->key != key || kb->mods != mods)
				keybindings_update_combo(kb, key, mods);

			if (! gtk_tree_model_iter_next(model, &child))
				break;
		}
		if (! gtk_tree_model_iter_next(model, &parent))
			return;
		gid++;
	}
}
