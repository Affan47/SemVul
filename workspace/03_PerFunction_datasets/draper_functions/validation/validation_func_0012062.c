_e2p_find_create_toggle_grouped_button (GtkWidget *box,
	findflag_t f, gboolean state, gchar *label, GtkWidget *leader,
	E2_FindDialogRuntime *rt)
{
	GtkWidget *button = _e2p_find_create_toggle_button_real (box, f, state, label,
		_e2p_find_grouptoggle_cb, rt);
	GtkWidget *ptr;
	GSList *members;
	if (leader == NULL)
	{
		ptr =	button;
		members = NULL;
		rt->groups = g_slist_append (rt->groups, button);
	}
	else
	{
		ptr = leader;
		members = g_object_get_data (G_OBJECT (leader), "group_members");
	}
	g_object_set_data (G_OBJECT (button), "group_leader", ptr);
	members = g_slist_append (members, button);
	g_object_set_data (G_OBJECT (ptr), "group_members", members);
	return button;
}
