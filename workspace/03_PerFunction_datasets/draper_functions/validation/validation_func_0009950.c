value_added_current_editor (AnjutaPlugin *plugin, const char *name,
							const GValue *value, gpointer data)
{
	GObject *editor;
	DebugManagerPlugin *self;

	self = ANJUTA_PLUGIN_DEBUG_MANAGER (plugin);

	editor = g_value_get_object (value);
	DEBUG_PRINT("add value current editor %p",  editor);

	if (!IANJUTA_IS_EDITOR(editor))
	{
		self->current_editor = NULL;
		return;
	}

	self->current_editor = IANJUTA_EDITOR (editor);
	g_object_add_weak_pointer (G_OBJECT (self->current_editor), (gpointer *)(gpointer)&self->current_editor);


	show_program_counter_in_editor (self);


	guint signal_id = g_signal_lookup( "line-marks-gutter-clicked", IANJUTA_TYPE_EDITOR);
	glong handler_id = g_signal_handler_find( (gpointer)self->current_editor,
            G_SIGNAL_MATCH_ID,
            signal_id,
            0, NULL, NULL, NULL );


	DEBUG_PRINT("current editor %p, breapoints db %p", self->current_editor, self->breakpoints);

	if(!handler_id) {
		g_signal_connect (
				self->current_editor,
				"line-marks-gutter-clicked",
				G_CALLBACK (breakpoint_toggle_handler),
				self->breakpoints
			);
	}

}
