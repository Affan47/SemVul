gsql_editor_finalize (GObject *obj)
{
	GSQL_TRACE_FUNC;

	GSQLEditor *editor = GSQL_EDITOR (obj);
	g_object_unref (editor->private->ui);
	g_free (editor->private);

	(* G_OBJECT_CLASS (parent_class)->finalize) (obj);

}
