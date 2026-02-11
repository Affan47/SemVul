rule_type_menu_new (VgRuleEditor *editor)
{
	GtkWidget *omenu, *menu, *item;
	int i;

	omenu = gtk_option_menu_new ();
	menu = gtk_menu_new ();

	for (i = 0; i < VG_RULE_LAST; i++) {
		item = gtk_menu_item_new_with_label (vg_rule_type_to_name (i));
		g_object_set_data ((GObject *) item, "vgrule_t", GINT_TO_POINTER (i));
		g_signal_connect (item, "activate", G_CALLBACK (type_menu_changed), editor);
		gtk_widget_show (item);
		gtk_menu_shell_append ((GtkMenuShell *) menu, item);
		editor->types[i] = item;
	}

	gtk_widget_show (menu);
	gtk_option_menu_set_menu ((GtkOptionMenu *) omenu, menu);

	return omenu;
}
