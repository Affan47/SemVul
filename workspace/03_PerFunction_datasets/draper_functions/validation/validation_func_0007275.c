e_reflow_dispose (GObject *object)
{
	EReflow *reflow = E_REFLOW (object);

	g_free (reflow->items);
	g_free (reflow->heights);
	g_free (reflow->columns);

	reflow->items          = NULL;
	reflow->heights        = NULL;
	reflow->columns        = NULL;
	reflow->count          = 0;
	reflow->allocated_count = 0;

	if (reflow->incarnate_idle_id)
		g_source_remove (reflow->incarnate_idle_id);
	reflow->incarnate_idle_id = 0;

	if (reflow->do_adjustment_idle_id)
		g_source_remove (reflow->do_adjustment_idle_id);
	reflow->do_adjustment_idle_id = 0;

	disconnect_model (reflow);
	disconnect_selection (reflow);

	g_free (reflow->empty_message);
	reflow->empty_message = NULL;

	if (reflow->sorter) {
		g_object_unref (reflow->sorter);
		reflow->sorter = NULL;
	}

	G_OBJECT_CLASS (e_reflow_parent_class)->dispose (object);
}
